#include "object.h"
#include <sstream>
#include <iomanip>
#include <functional>

namespace vcs {

/**
 * @brief Calculates a simple hash for input string using std::hash
 * @param input The string to hash
 * @return std::string Hexadecimal representation of the hash
 */
std::string calculateSimpleHash(const std::string& input) {
    std::size_t hash = std::hash<std::string>{}(input);
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

/**
 * @brief Constructs a Blob with content and optional file path
 * @param content The file content to store
 * @param path The original file path (default empty)
 */
Blob::Blob(const std::string& content, const std::string& path) 
    : content(content), file_path(path) {
    hash = calculateHash();
}

/**
 * @brief Calculates the SHA-1 hash of the blob content
 * @return std::string The calculated hash value
 */
std::string Blob::calculateHash() const {
    return calculateSimpleHash("blob:" + content);
}

/**
 * @brief Adds an entry to the tree
 * @param entry The TreeEntry to add
 */
void Tree::addEntry(const TreeEntry& entry) {
    entries.push_back(entry);
}

/**
 * @brief Serializes the tree to string format for storage
 * @return std::string Serialized tree representation
 */
std::string Tree::serialize() const {
    std::stringstream ss;
    for(const auto& entry : entries) {
        ss << entry.mode << " " << entry.type << " " << entry.hash << " " << entry.name << "\n";
    }
    return ss.str();
}

/**
 * @brief Calculates the SHA-1 hash of the serialized tree
 * @return std::string The calculated hash value
 */
std::string Tree::calculateHash() const {
    return calculateSimpleHash("tree:" + serialize());
}

/**
 * @brief Serializes the commit to string format for storage
 * @return std::string Serialized commit representation
 */
std::string Commit::serialize() const {
    std::stringstream ss;
    ss << "tree " << tree_hash << "\n";
    for(const auto& parent : parent_hashes) {
        ss << "parent " << parent << "\n";
    }
    ss << "author " << author << "\n";
    ss << "timestamp " << timestamp << "\n";
    ss << "\n" << message << "\n";
    return ss.str();
}

/**
 * @brief Calculates the SHA-1 hash of the serialized commit
 * @return std::string The calculated hash value
 */
std::string Commit::calculateHash() const {
    return calculateSimpleHash("commit:" + serialize());
}

} // namespace vcs