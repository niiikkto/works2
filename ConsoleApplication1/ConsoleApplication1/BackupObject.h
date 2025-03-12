#pragma once
#include <string>
#include <stdexcept>
#include <io.h>

class BackupObject {
private:
    std::string path;

public:
    explicit BackupObject(const std::string& filePath);
    std::string getPath() const;
    bool exists() const;
    std::string getName() const;
private:
    std::string extractFileName(const std::string& path) const;
};
