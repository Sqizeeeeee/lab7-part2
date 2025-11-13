#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "object.h"

namespace vcs {

/**
 * @brief Handles storage and retrieval of VCS objects from disk
 */
class Storage {
private:
    std::string objects_path;    ///< Path to the objects directory
    
    /**
     * @brief Generates full file path for an object based on its hash
     * @param hash The object's hash
     * @return std::string Full path to the object file
     */
    std::string getObjectPath(const std::string& hash) const;
    
public:
    /**
     * @brief Constructs Storage object and initializes objects path
     */
    Storage();
    
    /**
     * @brief Initializes the storage system by creating necessary directories
     * @return bool True if initialization successful, false otherwise
     */
    bool initialize();
    
    /**
     * @brief Stores a Blob object to disk
     * @param blob The Blob object to store
     * @return bool True if storage successful, false otherwise
     */
    bool storeBlob(const Blob& blob);
    
    /**
     * @brief Stores a Tree object to disk
     * @param tree The Tree object to store
     * @return bool True if storage successful, false otherwise
     */
    bool storeTree(const Tree& tree);
    
    /**
     * @brief Stores a Commit object to disk
     * @param commit The Commit object to store
     * @return bool True if storage successful, false otherwise
     */
    bool storeCommit(const Commit& commit);
    
    /**
     * @brief Reads a Blob object from disk by its hash
     * @param hash The hash of the Blob to read
     * @param blob Reference to Blob object to populate with data
     * @return bool True if read successful, false otherwise
     */
    bool readBlob(const std::string& hash, Blob& blob);
    
    /**
     * @brief Reads a Tree object from disk by its hash
     * @param hash The hash of the Tree to read
     * @param tree Reference to Tree object to populate with data
     * @return bool True if read successful, false otherwise
     */
    bool readTree(const std::string& hash, Tree& tree);
    
    /**
     * @brief Reads a Commit object from disk by its hash
     * @param hash The hash of the Commit to read
     * @param commit Reference to Commit object to populate with data
     * @return bool True if read successful, false otherwise
     */
    bool readCommit(const std::string& hash, Commit& commit);
    
    /**
     * @brief Checks if an object exists in storage by its hash
     * @param hash The hash to check
     * @return bool True if object exists, false otherwise
     */
    bool objectExists(const std::string& hash) const;
};

} // namespace vcs

#endif