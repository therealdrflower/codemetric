#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    std::string path = argv[1];
    std::ifstream file;
    int fileCount = 0;
    int totalLineCount = 0;

    std::cout << "Code metric software\n";
    std::cout << "Calculates files and line count in 1 folder\n\n";

    // Check if the directory exists
    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "Directory does not exist or is not accessible." << "\n";
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (!entry.is_regular_file()) {
            continue; // Skip if the entry is not a file
        }

        std::string filePath = entry.path().string();
        fileCount++;
        file.open(filePath);
        if (file.is_open()) {
            std::string line;
            int lineCount = 0;

            while (std::getline(file, line)) {
                lineCount++;
            }

            totalLineCount += lineCount;
            file.close();

            std::cout << "Number of lines in " << filePath << ": " << lineCount << "\n";
        } else {
            std::cout << "Failed to open " << filePath << "\n";
        }
    }

    std::cout << "Total number of files: " << fileCount << "\n";
    std::cout << "Total number of lines: " << totalLineCount << "\n";

    return 0;
}
