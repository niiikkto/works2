#include "BackupObject.h"

BackupObject::BackupObject(const std::string& filePath) : path(filePath) {
    if (!exists()) {
        throw std::runtime_error("File does not exist: " + filePath);
    }
}

std::string BackupObject::getPath() const {
    return path;
}

bool BackupObject::exists() const {
    return _access(path.c_str(), 0) == 0;
}

std::string BackupObject::getName() const {
    return extractFileName(path);
}

std::string BackupObject::extractFileName(const std::string& path) const {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}
