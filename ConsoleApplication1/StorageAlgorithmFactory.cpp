#include "StorageAlgorithmFactory.h"
#include "SingleStorageAlogorithm.h"
#include "SplitStorageAlogorithm.h"
#include <stdexcept>

std::shared_ptr<IStorageAlgorithm> StorageAlgorithmFactory::createStorageAlgorithm(StorageFormat format) {
    switch (format) {
        case StorageFormat::SINGLE_FILE:
            return std::make_shared<SingleStorageAlgorithm>();
        case StorageFormat::MULTIPLE_FILES:
            return std::make_shared<SplitStorageAlgorithm>();
        default:
            throw std::invalid_argument("Unknown storage format");
    }
} 