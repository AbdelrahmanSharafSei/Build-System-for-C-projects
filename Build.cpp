#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <regex> 
#include "Build.h"
#include "FileTrakker.h"

bool Build::is_cFile(std::filesystem::path f)
{
    auto fName=f.filename().string();
    std::basic_regex cFileRegex(".*(\\.cpp|\\.c|\\.h)");
    auto statues = std::regex_match(fName,cFileRegex);
    if (statues)
    {
        return true;
    }
    else
    {
        return false;
    }    
}


std::vector<std::filesystem::path> Build::getProjectFiles (const std::string projectPath)
{
    
    std::vector<std::filesystem::path> fileList;

        // Iterate over the std::filesystem::directory_entry elements using `auto`
        for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(projectPath, std::filesystem::directory_options::skip_permission_denied))
        {
            
            
                if(is_cFile(dir_entry))
                {
                    fileList.push_back(dir_entry);
                    
                }
                else
                {
                
                }                  
        } 

    return fileList;
}

void Build::Init_build(const std::string projectPath)
{
    FileList=getProjectFiles(projectPath);
    FileTrakker FT(FileList);
    FT.printtHashs();

}

std::vector<std::filesystem::path> Build::getFileList()
{
    return FileList;
}


