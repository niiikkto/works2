#include "BackupJob.h"
#include <algorithm>
#include <stdexcept>
#include <direct.h>
#include <errno.h>

bool BackupJob::createDirectory(const std::string& path) const {
    return _mkdir(path.c_str()) == 0;
}

BackupJob::BackupJob(const std::string& jobName, const std::string& path, std::shared_ptr<IStorageAlgorithm> algorithm)
    : name(jobName), storagePath(path), storageAlgorithm(algorithm) {
    if (!algorithm) {
        throw std::invalid_argument("Storage algorithm cannot be null");
    }
    if (!createDirectory(path)) {
        if (errno != EEXIST) {
            throw std::runtime_error("Failed to create storage directory: " + path);
        }
    }
}

void BackupJob::addObject(const BackupObject& object) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&](const BackupObject& obj) { return obj.getPath() == object.getPath(); });
    
    if (it == objects.end()) {
        objects.push_back(object);
    }
}

void BackupJob::removeObject(const std::string& objectPath) {
    auto it = std::find_if(objects.begin(), objects.end(),
        [&](const BackupObject& obj) { return obj.getPath() == objectPath; });
    
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void BackupJob::createRestorePoint(const std::string& pointName) {
    if (objects.empty()) {
        throw std::runtime_error("No objects to backup");
    }

    std::vector<std::string> filePaths;
    for (const auto& obj : objects) {
        filePaths.push_back(obj.getPath());
    }

    storageAlgorithm->store(filePaths, storagePath, pointName);
    restorePoints.emplace_back(pointName, objects);
}

const std::vector<RestorePoint>& BackupJob::getRestorePoints() const {
    return restorePoints;
}

const std::vector<BackupObject>& BackupJob::getObjects() const {
    return objects;
}

const std::string& BackupJob::getName() const {
    return name;
}

const std::string& BackupJob::getStoragePath() const {
    return storagePath;
}

void BackupJob::setStorageAlgorithm(std::shared_ptr<IStorageAlgorithm> algorithm) {
    if (!algorithm) {
        throw std::invalid_argument("Storage algorithm cannot be null");
    }
    storageAlgorithm = algorithm;
}
