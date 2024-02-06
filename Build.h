#ifndef BUILD_H
#define BUILD_H

#include <string>
#include <map>
#include <vector>
#include <filesystem>

class Build
{
    private:
        std::map<std::string,std::string> filesLog;
        std::vector<std::filesystem::path> getProjectFiles (const std::string projectPath);
    public:
        void Init_build(const std::string projectPath);
};

#endif