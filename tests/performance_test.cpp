#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "constants.h"
#include "storage.h"
#include "index.h"
#include "object.h"

namespace vcs {

class PerformanceTester {
private:
    Storage storage;
    Index index;
    std::ofstream csv_file;

public:
    PerformanceTester() {
        storage.initialize();
        
        // Создаем директорию data если её нет
        std::system("mkdir -p data");
        
        // Открываем CSV файл в директории data
        csv_file.open("data/performance_data.csv");
        
        // Заголовок CSV файла
        csv_file << "file_count,operation,time_microseconds\n";
    }

    void generateTestFiles(int count, int size_kb) {
        for (int i = 0; i < count; i++) {
            std::string filename = "test_file_" + std::to_string(i) + ".txt";
            std::ofstream file(filename);
            std::string content(size_kb * 1024, 'A' + (i % 26));
            file << content;
        }
    }

    void cleanupTestFiles(int count) {
        for (int i = 0; i < count; i++) {
            std::string filename = "test_file_" + std::to_string(i) + ".txt";
            std::remove(filename.c_str());
        }
    }

    void testAddPerformance(int file_count) {
        auto start = std::chrono::high_resolution_clock::now();
        
        for (int i = 0; i < file_count; i++) {
            std::string filename = "test_file_" + std::to_string(i) + ".txt";
            std::ifstream file(filename);
            std::string content((std::istreambuf_iterator<char>(file)), 
                               std::istreambuf_iterator<char>());
            
            Blob blob(content, filename);
            storage.storeBlob(blob);
            index.addFile(filename, blob.hash);
        }
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Записываем в CSV
        csv_file << file_count << ",add," << duration.count() << "\n";
        csv_file.flush();
        std::cout << "Add " << file_count << " files: " << duration.count() << " μs" << std::endl;
        
        index.clear();
    }

    void testCommitPerformance(int file_count) {
        // Сначала добавляем файлы
        for (int i = 0; i < file_count; i++) {
            std::string filename = "test_file_" + std::to_string(i) + ".txt";
            std::ifstream file(filename);
            std::string content((std::istreambuf_iterator<char>(file)), 
                               std::istreambuf_iterator<char>());
            
            Blob blob(content, filename);
            storage.storeBlob(blob);
            index.addFile(filename, blob.hash);
        }

        // Тестируем коммит
        auto start = std::chrono::high_resolution_clock::now();
        
        // Создаем tree из staged файлов
        Tree tree;
        auto staged_files = index.getStagedFiles();
        for (const auto& file_path : staged_files) {
            TreeEntry entry;
            entry.mode = "100644";
            entry.type = types::BLOB;
            entry.hash = "test_hash";
            entry.name = file_path;
            tree.addEntry(entry);
        }
        tree.hash = tree.calculateHash();
        storage.storeTree(tree);
        
        // Создаем коммит
        Commit commit;
        commit.tree_hash = tree.hash;
        commit.author = "tester";
        commit.message = "Performance test commit";
        commit.timestamp = "1234567890";
        commit.hash = commit.calculateHash();
        storage.storeCommit(commit);
        
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Записываем в CSV
        csv_file << file_count << ",commit," << duration.count() << "\n";
        csv_file.flush();
        std::cout << "Commit " << file_count << " files: " << duration.count() << " μs" << std::endl;
        
        index.clear();
    }

    void runPerformanceSuite() {
        std::vector<int> test_sizes = {10, 50, 100, 200, 500};
        
        std::cout << "Starting performance tests..." << std::endl;
        std::cout << "Results will be saved to data/performance_data.csv" << std::endl;
        std::cout << "Time measured in microseconds (μs)" << std::endl;
        std::cout << "==========================================" << std::endl;
        
        for (int size : test_sizes) {
            std::cout << "Testing with " << size << " files..." << std::endl;
            generateTestFiles(size, 1); // Файлы по 1KB
            
            testAddPerformance(size);
            testCommitPerformance(size);
            
            cleanupTestFiles(size);
            std::cout << "---" << std::endl;
        }
        
        csv_file.close();
        std::cout << "Performance tests completed!" << std::endl;
        std::cout << "Data saved to: data/performance_data.csv" << std::endl;
    }
};

} // namespace vcs

int main() {
    vcs::PerformanceTester tester;
    tester.runPerformanceSuite();
    return 0;
}