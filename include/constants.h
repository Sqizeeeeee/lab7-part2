#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <filesystem>

namespace vcs {

/**
 * @brief Main VCS directory name
 */
const std::string VCS_DIR = ".my_vcs";

/**
 * @brief Directory for storing VCS objects (blobs, trees, commits)
 */
const std::string OBJECTS_DIR = "objects";

/**
 * @brief Index file name for staging area
 */
const std::string INDEX_FILE = "index";

/**
 * @brief HEAD file name pointing to current branch/commit
 */
const std::string HEAD_FILE = "HEAD";

namespace types {
    /**
     * @brief Object type constant for file content storage
     */
    const std::string BLOB = "blob";

    /**
     * @brief Object type constant for directory structure
     */
    const std::string TREE = "tree";

    /**
     * @brief Object type constant for commit metadata
     */
    const std::string COMMIT = "commit";
}

} // namespace vcs

#endif