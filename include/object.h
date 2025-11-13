#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <vector>

namespace vcs {

struct Blob {
    std::string hash;
    std::string content;
    std::string file_path;
    
    Blob(const std::string& content, const std::string& path = "");
    std::string calculateHash() const;
};

struct TreeEntry {
    std::string mode;
    std::string type;
    std::string hash;
    std::string name;
};

struct Tree {
    std::string hash;
    std::vector<TreeEntry> entries;
    
    void addEntry(const TreeEntry& entry);
    std::string calculateHash() const;
    std::string serialize() const;
};

struct Commit {
    std::string hash;
    std::string tree_hash;
    std::vector<std::string> parent_hashes;
    std::string author;
    std::string message;
    std::string timestamp;
    
    std::string calculateHash() const;
    std::string serialize() const;
};

} // namespace vcs

#endif