#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include "Build.h"

std::vector<std::filesystem::path> Build::getProjectFiles (const std::string projectPath)
{
    std::vector<std::filesystem::path> fileList;
    try 
    {
        for (const auto& entry : std::filesystem::directory_iterator(projectPath)) 
        {
            std::cout << entry.path().filename() << std::endl;
            fileList.push_back(std::to_string(5));
        }
    } 
    catch (const std::filesystem::filesystem_error& ex) 
    {
        std::cerr << "Error accessing folder: " << ex.what() << std::endl;
    }
    return fileList;
}

void Build::Init_build(const std::string projectPath)
{
    std::vector<std::filesystem::path> fileList=getProjectFiles(projectPath);
}

/*[4:41 PM] Abdelrahman Sharaf
list of files in a folder
[4:43 PM] Abdelrahman Sharaf
#include <iostream>
#include <filesystem>
 
int main() {
    const std::string folderPath = "/path/to/your/folder"; // Replace with your folder path
 
    try {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            std::cout << entry.path().filename() << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& ex) {
        std::cerr << "Error accessing folder: " << ex.what() << std::endl;
        return 1;
    }
 
    return 0;
}*/