#ifndef INDEX_H
#define INDEX_H

#include <string>
#include <vector>
#include <unordered_map>

namespace vcs {

struct IndexEntry {
    std::string file_path;
    std::string blob_hash;
    std::uint64_t timestamp;
    
    IndexEntry();
    IndexEntry(const std::string& path, const std::string& hash);
};

class Index {
private:
    std::string index_path;
    std::unordered_map<std::string, IndexEntry> entries;
    
    bool loadFromDisk();
    bool saveToDisk();
    
public:
    Index();
    
    bool addFile(const std::string& file_path, const std::string& blob_hash);
    bool removeFile(const std::string& file_path);
    bool containsFile(const std::string& file_path) const;
    
    std::vector<std::string> getStagedFiles() const;
    bool isClean() const;
    
    void clear();
};

} // namespace vcs

#endif