#pragma once
#include "IStorageAlorithm.h"
#include <string>

class SplitStorageAlgorithm : public IStorageAlgorithm {
public:
    void store(const std::vector<std::string>& files, const std::string& destinationPath, const std::string& pointName) override;
    std::string getAlgorithmName() const override;
private:
    bool createDirectory(const std::string& path) const;
    std::string extractFileName(const std::string& path) const;
};
