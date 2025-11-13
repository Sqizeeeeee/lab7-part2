#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "constants.h"
#include "storage.h"
#include "index.h"
#include "object.h"

namespace vcs {

class VCSController {
private:
    Storage storage;
    Index index;

    std::string getCurrentTimestamp() {
        std::time_t now = std::time(nullptr);
        return std::to_string(now);
    }

public:
    VCSController() {
        storage.initialize();
    }

    bool init() {
        return storage.initialize();
    }

    bool add(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file " << file_path << std::endl;
            return false;
        }

        std::string content((std::istreambuf_iterator<char>(file)), 
                           std::istreambuf_iterator<char>());
        
        Blob blob(content, file_path);
        if (!storage.storeBlob(blob)) {
            std::cerr << "Error: Failed to store blob" << std::endl;
            return false;
        }

        return index.addFile(file_path, blob.hash);
    }

    bool commit(const std::string& message, const std::string& author = "user") {
        if (index.isClean()) {
            std::cerr << "Error: No changes to commit" << std::endl;
            return false;
        }

        // Создаем tree из staged файлов
        Tree tree;
        auto staged_files = index.getStagedFiles();
        for (const auto& file_path : staged_files) {
            TreeEntry entry;
            entry.mode = "100644";
            entry.type = types::BLOB;
            entry.hash = index.containsFile(file_path) ? "hash_placeholder" : ""; // Нужно получить реальный hash
            entry.name = file_path;
            tree.addEntry(entry);
        }
        tree.hash = tree.calculateHash();
        
        if (!storage.storeTree(tree)) {
            std::cerr << "Error: Failed to store tree" << std::endl;
            return false;
        }

        // Создаем коммит
        Commit commit;
        commit.tree_hash = tree.hash;
        commit.author = author;
        commit.message = message;
        commit.timestamp = getCurrentTimestamp();
        commit.hash = commit.calculateHash();

        if (!storage.storeCommit(commit)) {
            std::cerr << "Error: Failed to store commit" << std::endl;
            return false;
        }

        // Очищаем индекс после успешного коммита
        index.clear();
        std::cout << "Committed: " << message << std::endl;
        return true;
    }

    void status() {
        auto staged_files = index.getStagedFiles();
        std::cout << "Staged files:" << std::endl;
        for (const auto& file : staged_files) {
            std::cout << "  " << file << std::endl;
        }
    }
};

void printUsage() {
    std::cout << "Usage: myvcs <command> [args]" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  init    - Initialize repository" << std::endl;
    std::cout << "  add     - Add file to index" << std::endl;
    std::cout << "  commit  - Create commit" << std::endl;
    std::cout << "  status  - Show status" << std::endl;
}

} // namespace vcs

int main(int argc, char* argv[]) {
    if (argc < 2) {
        vcs::printUsage();
        return 1;
    }

    vcs::VCSController controller;
    std::string command = argv[1];

    if (command == "init") {
        if (controller.init()) {
            std::cout << "Initialized empty VCS repository" << std::endl;
        }
    }
    else if (command == "add") {
        if (argc < 3) {
            std::cerr << "Error: No file specified" << std::endl;
            return 1;
        }
        controller.add(argv[2]);
    }
    else if (command == "commit") {
        if (argc < 3) {
            std::cerr << "Error: No commit message specified" << std::endl;
            return 1;
        }
        controller.commit(argv[2]);
    }
    else if (command == "status") {
        controller.status();
    }
    else {
        std::cerr << "Unknown command: " << command << std::endl;
        vcs::printUsage();
        return 1;
    }

    return 0;
}