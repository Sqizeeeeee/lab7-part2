#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <unordered_map>

namespace vcs {

/**
 * @brief Represents a single entry in the staging area index
 */
struct IndexEntry {
    std::string file_path;      ///< Path to the file in working directory
    std::string blob_hash;      ///< Hash of the file content (Blob)
    std::uint64_t timestamp;    ///< Timestamp when file was added to index
    
    /**
     * @brief Default constructor for IndexEntry
     */
    IndexEntry();
    
    /**
     * @brief Constructs an IndexEntry with file path and blob hash
     * @param path The file path
     * @param hash The blob hash of file content
     */
    IndexEntry(const std::string& path, const std::string& hash);
};

/**
 * @brief Manages the staging area (index) for tracking files to be committed
 */
class Index {
private:
    std::string index_path;     ///< Path to the index file on disk
    std::unordered_map<std::string, IndexEntry> entries;  ///< Map of staged files (path -> entry)
    
    /**
     * @brief Loads index entries from disk storage
     * @return bool True if load successful, false otherwise
     */
    bool loadFromDisk();
    
    /**
     * @brief Saves index entries to disk storage
     * @return bool True if save successful, false otherwise
     */
    bool saveToDisk();
    
public:
    /**
     * @brief Constructs Index object and loads existing index from disk
     */
    Index();
    
    /**
     * @brief Adds a file to the staging area index
     * @param file_path Path to the file to add
     * @param blob_hash Hash of the file's blob content
     * @return bool True if add successful, false otherwise
     */
    bool addFile(const std::string& file_path, const std::string& blob_hash);
    
    /**
     * @brief Removes a file from the staging area index
     * @param file_path Path to the file to remove
     * @return bool True if remove successful, false if file not found
     */
    bool removeFile(const std::string& file_path);
    
    /**
     * @brief Checks if a file is currently staged in the index
     * @param file_path Path to the file to check
     * @return bool True if file is staged, false otherwise
     */
    bool containsFile(const std::string& file_path) const;
    
    /**
     * @brief Gets list of all file paths currently staged in index
     * @return std::vector<std::string> List of staged file paths
     */
    std::vector<std::string> getStagedFiles() const;
    
    /**
     * @brief Checks if the index is empty (no staged files)
     * @return bool True if index is empty, false otherwise
     */
    bool isClean() const;
    
    /**
     * @brief Clears all entries from the index and removes index file from disk
     */
    void clear();
};

} // namespace vcs

#endif