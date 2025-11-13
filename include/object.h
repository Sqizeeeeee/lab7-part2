#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

namespace vcs {

/**
 * @brief Represents a file object in the VCS (stores file content)
 */
struct Blob {
    std::string hash;           ///< SHA-1 hash of the blob content
    std::string content;        ///< Actual file content
    std::string file_path;      ///< Original file path
    
    /**
     * @brief Constructs a Blob object with content and optional path
     * @param content The file content to store
     * @param path The original file path (default empty)
     */
    Blob(const std::string& content, const std::string& path = "");
    
    /**
     * @brief Calculates the SHA-1 hash of the blob content
     * @return std::string The calculated hash value
     */
    std::string calculateHash() const;
};

/**
 * @brief Represents an entry in a Tree object (file or directory reference)
 */
struct TreeEntry {
    std::string mode;    ///< File permissions mode (e.g., "100644")
    std::string type;    ///< Object type ("blob" or "tree")
    std::string hash;    ///< Hash of the referenced object
    std::string name;    ///< File or directory name
};

/**
 * @brief Represents a directory structure in the VCS
 */
struct Tree {
    std::string hash;                       ///< SHA-1 hash of the serialized tree
    std::vector<TreeEntry> entries;         ///< List of entries in the directory
    
    /**
     * @brief Adds an entry to the tree
     * @param entry The TreeEntry to add
     */
    void addEntry(const TreeEntry& entry);
    
    /**
     * @brief Calculates the SHA-1 hash of the serialized tree
     * @return std::string The calculated hash value
     */
    std::string calculateHash() const;
    
    /**
     * @brief Serializes the tree to string format for storage
     * @return std::string Serialized tree representation
     */
    std::string serialize() const;
};

/**
 * @brief Represents a commit object with metadata and references
 */
struct Commit {
    std::string hash;                       ///< SHA-1 hash of the commit
    std::string tree_hash;                  ///< Hash of the root tree object
    std::vector<std::string> parent_hashes; ///< List of parent commit hashes
    std::string author;                     ///< Commit author information
    std::string message;                    ///< Commit message
    std::string timestamp;                  ///< Commit timestamp
    
    /**
     * @brief Calculates the SHA-1 hash of the serialized commit
     * @return std::string The calculated hash value
     */
    std::string calculateHash() const;
    
    /**
     * @brief Serializes the commit to string format for storage
     * @return std::string Serialized commit representation
     */
    std::string serialize() const;
};

} // namespace vcs

#endif