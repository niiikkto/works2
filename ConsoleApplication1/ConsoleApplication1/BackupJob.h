#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IStorageAlorithm.h"
#include "BackupObject.h"
#include "RestorePoint.h"

class BackupJob {
private:
    std::string name;
    std::string storagePath;
    std::vector<BackupObject> objects;
    std::vector<RestorePoint> restorePoints;
    std::shared_ptr<IStorageAlgorithm> storageAlgorithm;

    bool createDirectory(const std::string& path) const;

public:
    BackupJob(const std::string& jobName, const std::string& path, std::shared_ptr<IStorageAlgorithm> algorithm);

    void addObject(const BackupObject& object);
    void removeObject(const std::string& objectPath);
    void createRestorePoint(const std::string& pointName);
    
    const std::vector<RestorePoint>& getRestorePoints() const;
    const std::vector<BackupObject>& getObjects() const;
    const std::string& getName() const;
    const std::string& getStoragePath() const;
    
    void setStorageAlgorithm(std::shared_ptr<IStorageAlgorithm> algorithm);
};
