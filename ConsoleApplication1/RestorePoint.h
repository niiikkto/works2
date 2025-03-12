#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "BackupObject.h"

class RestorePoint {
private:
    std::string name;
    std::vector<BackupObject> objects;
    std::chrono::system_clock::time_point creationTime;

public:
    explicit RestorePoint(const std::string& pointName, const std::vector<BackupObject>& backupObjects);
    
    const std::string& getName() const;
    const std::vector<BackupObject>& getObjects() const;
    std::chrono::system_clock::time_point getCreationTime() const;
};
