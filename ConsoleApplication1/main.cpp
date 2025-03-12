// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <direct.h>
#include <limits>
#include <errno.h>
#include "BackupJob.h"
#include "StorageAlgorithmFactory.h"
#include "SingleStorageAlogorithm.h"
#include "SplitStorageAlogorithm.h"

using namespace std;

// Helper function to create directory
bool createDirectory(const string& path) {
    return _mkdir(path.c_str()) == 0;
}

void createTestFiles() {
    // Create test directory and files
    if (!createDirectory("test_files")) {
        // Ignore error if directory already exists
        if (errno != EEXIST) {
            throw runtime_error("Failed to create test_files directory");
        }
    }
    
    ofstream file1("test_files/file1.txt");
    if (!file1.is_open()) {
        throw runtime_error("Failed to create file1.txt");
    }
    file1 << "This is test file 1" << endl;
    file1.close();
    
    ofstream file2("test_files/file2.txt");
    if (!file2.is_open()) {
        throw runtime_error("Failed to create file2.txt");
    }
    file2 << "This is test file 2" << endl;
    file2.close();
}

StorageFormat getStorageFormatFromUser() {
    while (true) {
        cout << "Select storage format:" << endl;
        cout << "1. Single file (all files in one archive)" << endl;
        cout << "2. Multiple files (separate archive for each file)" << endl;
        cout << "Enter your choice (1 or 2): ";
        
        int choice;
        cin >> choice;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 1 or 2." << endl;
            continue;
        }
        
        switch (choice) {
            case 1:
                return StorageFormat::SINGLE_FILE;
            case 2:
                return StorageFormat::MULTIPLE_FILES;
            default:
                cout << "Invalid choice. Please enter 1 or 2." << endl;
                continue;
        }
    }
}

void demonstrateBackup() {
    try {
        // Create test files
        createTestFiles();

        // Create backup storage directory
        if (!createDirectory("backups")) {
            // Ignore error if directory already exists
            if (errno != EEXIST) {
                throw runtime_error("Failed to create backups directory");
            }
        }

        // Get storage format from user
        StorageFormat format = getStorageFormatFromUser();
        
        // Create backup job with selected storage format
        shared_ptr<IStorageAlgorithm> storage;
        if (format == StorageFormat::SINGLE_FILE) {
            storage = make_shared<SingleStorageAlgorithm>();
        } else {
            storage = make_shared<SplitStorageAlgorithm>();
        }
        
        BackupJob job1("TestJob1", "backups/backup_storage", storage);

        // Add backup objects
        job1.addObject(BackupObject("test_files/file1.txt"));
        job1.addObject(BackupObject("test_files/file2.txt"));

        // Create restore point
        cout << "Creating restore point with " << storage->getAlgorithmName() << "..." << endl;
        job1.createRestorePoint("point1");

        // Ask user if they want to change format
        cout << "\nDo you want to change storage format? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            format = (format == StorageFormat::SINGLE_FILE) ? 
                    StorageFormat::MULTIPLE_FILES : StorageFormat::SINGLE_FILE;
                    
            shared_ptr<IStorageAlgorithm> newStorage;
            if (format == StorageFormat::SINGLE_FILE) {
                newStorage = make_shared<SingleStorageAlgorithm>();
            } else {
                newStorage = make_shared<SplitStorageAlgorithm>();
            }
            
            job1.setStorageAlgorithm(newStorage);
            
            cout << "Creating restore point with " << newStorage->getAlgorithmName() << "..." << endl;
            job1.createRestorePoint("point2");
        }

        // Print restore points information
        cout << "\nRestore points created:" << endl;
        for (const auto& point : job1.getRestorePoints()) {
            cout << "Point: " << point.getName() << endl;
            cout << "Objects:" << endl;
            for (const auto& obj : point.getObjects()) {
                cout << "  - " << obj.getPath() << endl;
            }
            cout << endl;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    demonstrateBackup();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
