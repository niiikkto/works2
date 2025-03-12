#pragma once
#include "IStorageAlorithm.h"
#include "SingleStorageAlogorithm.h"
#include "SplitStorageAlogorithm.h"
#include <memory>

class StorageAlgorithmFactory {
public:
    static std::shared_ptr<IStorageAlgorithm> createStorageAlgorithm(StorageFormat format);
}; 