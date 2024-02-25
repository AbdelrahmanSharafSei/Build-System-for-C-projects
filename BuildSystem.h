#ifndef BUILD_H
#define BUILD_H

#include <string>
#include <map>
#include <vector>
#include <filesystem>

class BuildSystem
{
    private:
        std::vector<std::filesystem::path> FileList;
        
        std::vector<std::filesystem::path> getProjectFiles (const std::string projectPath);

        bool is_cFile(std::filesystem::path f);
        bool isInitProjectFilesGenerated(const std::string projectPath);
        bool Staged;
    public:
        BuildSystem(const std::string projectPath);
        std::vector<std::filesystem::path> getFileList();
        
};

#endif