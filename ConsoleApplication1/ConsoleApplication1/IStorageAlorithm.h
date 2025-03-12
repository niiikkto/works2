#pragma once
#include <string>
#include <vector>
#include <memory>

enum class StorageFormat {
    SINGLE_FILE,
    MULTIPLE_FILES
};

class IStorageAlgorithm {
public:
    virtual ~IStorageAlgorithm() = default;
    virtual void store(const std::vector<std::string>& files, const std::string& destinationPath, const std::string& pointName) = 0;
    virtual std::string getAlgorithmName() const = 0;
};
