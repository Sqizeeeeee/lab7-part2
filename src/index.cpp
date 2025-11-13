#include "index.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <ctime>

namespace vcs {

IndexEntry::IndexEntry() : timestamp(0) {}

IndexEntry::IndexEntry(const std::string& path, const std::string& hash)
: file_path(path), blob_hash(hash) {
    timestamp = std::time(nullptr);
}

Index::Index() {
    index_path = std::string(VCS_DIR) + "/" + INDEX_FILE;
    loadFromDisk();
}

bool Index::loadFromDisk() {
    std::ifstream file(index_path);
    if (!file.is_open()) return false;
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string path, hash;
        std::uint64_t ts;
        if (iss >> path >> hash >> ts) {
            entries[path] = IndexEntry(path, hash);
            entries[path].timestamp = ts;
        }
    }
    return true;
}

bool Index::saveToDisk() {
    std::ofstream file(index_path);
    if (!file.is_open()) return false;
    
    for (const auto& pair : entries) {
        file << pair.second.file_path << " " 
             << pair.second.blob_hash << " " 
             << pair.second.timestamp << "\n";
    }
    return file.good();
}

bool Index::addFile(const std::string& file_path, const std::string& blob_hash) {
    entries[file_path] = IndexEntry(file_path, blob_hash);
    return saveToDisk();
}

bool Index::removeFile(const std::string& file_path) {
    auto it = entries.find(file_path);
    if (it != entries.end()) {
        entries.erase(it);
        return saveToDisk();
    }
    return false;
}

bool Index::containsFile(const std::string& file_path) const {
    return entries.find(file_path) != entries.end();
}

std::vector<std::string> Index::getStagedFiles() const {
    std::vector<std::string> result;
    for (const auto& pair : entries) {
        result.push_back(pair.first);
    }
    return result;
}

bool Index::isClean() const {
    return entries.empty();
}

void Index::clear() {
    entries.clear();
    std::remove(index_path.c_str());
}
}
