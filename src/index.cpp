#include "index.h"
#include "constants.h"
#include <fstream>
#include <sstream>
#include <ctime>

namespace vcs {

/**
 * @brief Default constructor for IndexEntry
 */
IndexEntry::IndexEntry() : timestamp(0) {}

/**
 * @brief Constructs an IndexEntry with file path and blob hash
 * @param path The file path
 * @param hash The blob hash of file content
 */
IndexEntry::IndexEntry(const std::string& path, const std::string& hash)
: file_path(path), blob_hash(hash) {
    timestamp = std::time(nullptr);
}

/**
 * @brief Constructs Index object and loads existing index from disk
 */
Index::Index() {
    index_path = std::string(VCS_DIR) + "/" + INDEX_FILE;
    loadFromDisk();
}

/**
 * @brief Loads index entries from disk storage
 * @return bool True if load successful, false otherwise
 */
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

/**
 * @brief Saves index entries to disk storage
 * @return bool True if save successful, false otherwise
 */
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

/**
 * @brief Adds a file to the staging area index
 * @param file_path Path to the file to add
 * @param blob_hash Hash of the file's blob content
 * @return bool True if add successful, false otherwise
 */
bool Index::addFile(const std::string& file_path, const std::string& blob_hash) {
    entries[file_path] = IndexEntry(file_path, blob_hash);
    return saveToDisk();
}

/**
 * @brief Removes a file from the staging area index
 * @param file_path Path to the file to remove
 * @return bool True if remove successful, false if file not found
 */
bool Index::removeFile(const std::string& file_path) {
    auto it = entries.find(file_path);
    if (it != entries.end()) {
        entries.erase(it);
        return saveToDisk();
    }
    return false;
}

/**
 * @brief Checks if a file is currently staged in the index
 * @param file_path Path to the file to check
 * @return bool True if file is staged, false otherwise
 */
bool Index::containsFile(const std::string& file_path) const {
    return entries.find(file_path) != entries.end();
}

/**
 * @brief Gets list of all file paths currently staged in index
 * @return std::vector<std::string> List of staged file paths
 */
std::vector<std::string> Index::getStagedFiles() const {
    std::vector<std::string> result;
    for (const auto& pair : entries) {
        result.push_back(pair.first);
    }
    return result;
}

/**
 * @brief Checks if the index is empty (no staged files)
 * @return bool True if index is empty, false otherwise
 */
bool Index::isClean() const {
    return entries.empty();
}

/**
 * @brief Clears all entries from the index and removes index file from disk
 */
void Index::clear() {
    entries.clear();
    std::remove(index_path.c_str());
}

} // namespace vcs