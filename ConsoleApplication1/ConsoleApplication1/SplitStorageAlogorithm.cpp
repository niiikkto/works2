#include "SplitStorageAlogorithm.h"
#include <stdexcept>
#include <direct.h>
#include <io.h>

bool SplitStorageAlgorithm::createDirectory(const std::string& path) const {
    return _mkdir(path.c_str()) == 0;
}

std::string SplitStorageAlgorithm::extractFileName(const std::string& path) const {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

void SplitStorageAlgorithm::store(const std::vector<std::string>& files, const std::string& destinationPath, const std::string& pointName) {
    // Create destination directory if it doesn't exist
    if (!createDirectory(destinationPath)) {
        if (errno != EEXIST) {
            throw std::runtime_error("Failed to create destination directory");
        }
    }

    for (const auto& file : files) {
        if (_access(file.c_str(), 0) != 0) {
            throw std::runtime_error("File does not exist: " + file);
        }

        std::string fileName = extractFileName(file);
        std::string zipName = destinationPath + "/" + pointName + "_" + fileName + ".zip";

        // Create ZIP archive command
        std::string command = "powershell Compress-Archive -Path \"" + file + "\" -DestinationPath \"" + zipName + "\" -Force";
        int result = system(command.c_str());

        if (result != 0) {
            throw std::runtime_error("Failed to create ZIP archive for file: " + file);
        }
    }
}

std::string SplitStorageAlgorithm::getAlgorithmName() const {
    return "Split Storage";
}
