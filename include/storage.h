#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "object.h"

namespace vcs {

class Storage {
private:
    std::string objects_path;
    
    std::string getObjectPath(const std::string& hash) const;
    
public:
    Storage();
    bool initialize();
    
    bool storeBlob(const Blob& blob);
    bool storeTree(const Tree& tree);
    bool storeCommit(const Commit& commit);
    
    bool readBlob(const std::string& hash, Blob& blob);
    bool readTree(const std::string& hash, Tree& tree);
    bool readCommit(const std::string& hash, Commit& commit);
    
    bool objectExists(const std::string& hash) const;
};

} // namespace vcs

#endif