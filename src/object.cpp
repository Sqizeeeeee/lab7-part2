#include "object.h"
#include <sstream>
#include <iomanip>
#include <functional>

namespace vcs {


std::string calculateSimpleHash(const std::string& input) {
    std::size_t hash = std::hash<std::string>{}(input);
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash;
    return ss.str();
}

Blob::Blob(const std::string& content, const std::string& path) 
    : content(content), file_path(path) {
    hash = calculateHash();
}

std::string Blob::calculateHash() const {
    return calculateSimpleHash("blob:" + content);
}

void Tree::addEntry(const TreeEntry& entry) {
    entries.push_back(entry);
}

std::string Tree::serialize() const {
    std::stringstream ss;
    for(const auto& entry : entries) {
        ss << entry.mode << " " << entry.type << " " << entry.hash << " " << entry.name << "\n";
    }
    return ss.str();
}

std::string Tree::calculateHash() const {
    return calculateSimpleHash("tree:" + serialize());
}

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

std::string Commit::calculateHash() const {
    return calculateSimpleHash("commit:" + serialize());
}

} // namespace vcs