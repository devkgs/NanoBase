#include "FileStorage.h"

#include <fstream>
#include <sstream>

void FileStorage::save(const std::string &content) {
    std::ofstream file(filename_, std::ios::out | std::ios::trunc);

    if (file.is_open()) {
        file << content;
    }
}

std::optional<std::string> FileStorage::load() {
    std::ifstream file(filename_);

    if (!file.is_open()) {
        return std::nullopt;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
