#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

void find_directory(const fs::path& path, const std::string& dir_name) {
    try {
        // Iterate over the directory and its subdirectories
        for (const auto& entry : fs::recursive_directory_iterator(path)) {
            // Check if the current entry is a directory and its name matches the target
            if (entry.is_directory() && entry.path().filename() == dir_name) {
                std::cout << "Found directory: " << entry.path() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    std::string dir_to_search = "/";  // Starting directory (could be set to any path)
    std::string dir_name = "mydir";   // The directory name to search for

    // Call the function to start searching
    find_directory(dir_to_search, dir_name);

    return 0;
}
