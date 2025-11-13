#include "storage.h"
#include "constants.h"
#include <fstream>
#include <iostream>
#include <sys/stat.h> // для mkdir
#include <cstdio>     // для remove

namespace vcs {

/**
 * @brief Constructs Storage object and initializes objects path
 */
Storage::Storage() {
    objects_path = std::string(VCS_DIR) + "/" + OBJECTS_DIR;
}

/**
 * @brief Initializes the storage system by creating necessary directories
 * @return bool True if initialization successful, false otherwise
 */
bool Storage::initialize() {
    // Create directories using system calls
    if (mkdir(VCS_DIR.c_str(), 0755) != 0) {
        // Ignore error if directory already exists
    }
    
    if (mkdir(objects_path.c_str(), 0755) != 0) {
        // Ignore error if directory already exists
    }
    return true;
}

/**
 * @brief Generates full file path for an object based on its hash
 * @param hash The object's hash
 * @return std::string Full path to the object file
 */
std::string Storage::getObjectPath(const std::string& hash) const {
    return objects_path + "/" + hash;
}

/**
 * @brief Stores a Blob object to disk
 * @param blob The Blob object to store
 * @return bool True if storage successful, false otherwise
 */
bool Storage::storeBlob(const Blob& blob) {
    std::ofstream file(getObjectPath(blob.hash));
    if (!file.is_open()) return false;
    file << blob.content;
    return file.good();
}

/**
 * @brief Stores a Tree object to disk
 * @param tree The Tree object to store
 * @return bool True if storage successful, false otherwise
 */
bool Storage::storeTree(const Tree& tree) {
    std::ofstream file(getObjectPath(tree.hash));
    if (!file.is_open()) return false;
    file << tree.serialize();
    return file.good();
}

/**
 * @brief Stores a Commit object to disk
 * @param commit The Commit object to store
 * @return bool True if storage successful, false otherwise
 */
bool Storage::storeCommit(const Commit& commit) {
    std::ofstream file(getObjectPath(commit.hash));
    if (!file.is_open()) return false;
    file << commit.serialize();
    return file.good();
}

/**
 * @brief Reads a Blob object from disk by its hash
 * @param hash The hash of the Blob to read
 * @param blob Reference to Blob object to populate with data
 * @return bool True if read successful, false otherwise
 */
bool Storage::readBlob(const std::string& hash, Blob& blob) {
    std::ifstream file(getObjectPath(hash));
    if (!file.is_open()) return false;
    
    std::string content((std::istreambuf_iterator<char>(file)), 
                       std::istreambuf_iterator<char>());
    blob = Blob(content);
    return true;
}

/**
 * @brief Checks if an object exists in storage by its hash
 * @param hash The hash to check
 * @return bool True if object exists, false otherwise
 */
bool Storage::objectExists(const std::string& hash) const {
    std::ifstream file(getObjectPath(hash));
    return file.good();
}

} // namespace vcs