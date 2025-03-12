#include "SingleStorageAlogorithm.h"
#include <stdexcept>
#include <direct.h>
#include <io.h>

bool SingleStorageAlgorithm::createDirectory(const std::string& path) const {
    return _mkdir(path.c_str()) == 0;
}

std::string SingleStorageAlgorithm::extractFileName(const std::string& path) const {
    size_t pos = path.find_last_of("/\\");
    if (pos == std::string::npos) {
        return path;
    }
    return path.substr(pos + 1);
}

void SingleStorageAlgorithm::store(const std::vector<std::string>& files, const std::string& destinationPath, const std::string& pointName) {
    // Create destination directory if it doesn't exist
    if (!createDirectory(destinationPath)) {
        if (errno != EEXIST) {
            throw std::runtime_error("Failed to create destination directory");
        }
    }

    // Create a temporary directory for files
    std::string tempDir = destinationPath + "/temp_" + pointName;
    if (!createDirectory(tempDir)) {
        throw std::runtime_error("Failed to create temporary directory");
    }

    // Copy all files to temporary directory
    for (const auto& file : files) {
        if (_access(file.c_str(), 0) != 0) {
            throw std::runtime_error("File does not exist: " + file);
        }

        std::string fileName = extractFileName(file);
        std::string destPath = tempDir + "/" + fileName;

        // Use Windows copy command
        std::string copyCmd = "copy /Y \"" + file + "\" \"" + destPath + "\" > nul";
        if (system(copyCmd.c_str()) != 0) {
            system(("rmdir /S /Q \"" + tempDir + "\"").c_str());
            throw std::runtime_error("Failed to copy file: " + file);
        }
    }

    // Create ZIP archive
    std::string zipName = destinationPath + "/" + pointName + "_backup.zip";
    std::string command = "powershell Compress-Archive -Path \"" + tempDir + "/*\" -DestinationPath \"" + zipName + "\" -Force";
    int result = system(command.c_str());

    // Cleanup temporary directory
    system(("rmdir /S /Q \"" + tempDir + "\"").c_str());

    if (result != 0) {
        throw std::runtime_error("Failed to create ZIP archive");
    }
}

std::string SingleStorageAlgorithm::getAlgorithmName() const {
    return "Single Storage";
}
