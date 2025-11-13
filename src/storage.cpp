#include "storage.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h> // для mkdir
#include <cstdio>     // для remove

namespace vcs {

Storage::Storage() {
    objects_path = std::string(VCS_DIR) + "/" + OBJECTS_DIR;
}

bool Storage::initialize() {
    // Создаем директорию используя системные вызовы
    if (mkdir(VCS_DIR.c_str(), 0755) != 0) {
        // Игнорируем ошибку если директория уже существует
    }
    
    if (mkdir(objects_path.c_str(), 0755) != 0) {
        // Игнорируем ошибку если директория уже существует
    }
    return true;
}

std::string Storage::getObjectPath(const std::string& hash) const {
    return objects_path + "/" + hash;
}

bool Storage::storeBlob(const Blob& blob) {
    std::ofstream file(getObjectPath(blob.hash));
    if (!file.is_open()) return false;
    file << blob.content;
    return file.good();
}

bool Storage::storeTree(const Tree& tree) {
    std::ofstream file(getObjectPath(tree.hash));
    if (!file.is_open()) return false;
    file << tree.serialize();
    return file.good();
}

bool Storage::storeCommit(const Commit& commit) {
    std::ofstream file(getObjectPath(commit.hash));
    if (!file.is_open()) return false;
    file << commit.serialize();
    return file.good();
}

bool Storage::readBlob(const std::string& hash, Blob& blob) {
    std::ifstream file(getObjectPath(hash));
    if (!file.is_open()) return false;
    
    std::string content((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>());
    blob = Blob(content);
    return true;
}

bool Storage::objectExists(const std::string& hash) const {
    std::ifstream file(getObjectPath(hash));
    return file.good();
}

} // namespace vcs