#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <filesystem>

namespace vcs {

const std::string VCS_DIR = ".my_vcs";
const std::string OBJECTS_DIR = "objects";
const std::string INDEX_FILE = "index";
const std::string HEAD_FILE = "HEAD";

namespace types {
    const std::string BLOB = "blob";
    const std::string TREE = "tree";
    const std::string COMMIT = "commit";
}

} // namespace vcs

#endif