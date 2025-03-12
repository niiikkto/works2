#include "RestorePoint.h"

RestorePoint::RestorePoint(const std::string& pointName, const std::vector<BackupObject>& backupObjects)
    : name(pointName), objects(backupObjects), creationTime(std::chrono::system_clock::now()) {}

const std::string& RestorePoint::getName() const {
    return name;
}

const std::vector<BackupObject>& RestorePoint::getObjects() const {
    return objects;
}

std::chrono::system_clock::time_point RestorePoint::getCreationTime() const {
    return creationTime;
}
