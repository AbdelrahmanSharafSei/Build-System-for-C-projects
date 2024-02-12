#include <iostream>
#include <filesystem>
#include <string>
#include <map>
#include <vector>
#include <regex> 
#include "Build.h"

bool Build::is_cFile(std::filesystem::path f)
{
    auto fName=f.filename().string();
    std::basic_regex cFileRegex(".*(\\.cpp|\\.c|\\.h|\\.py)");
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
            std::cout<<dir_entry<<std::endl;
            
                if(is_cFile(dir_entry))
                {
                    fileList.push_back(dir_entry);
                    // std::cout<<"i am Cfile"<<std::endl;
                }
                else
                {
                // std::cout<<"i am here"<<std::endl;
                }       
           
            //  std::cout<<"all files"<<std::endl;

    } 

    // std::cout<<"all files b"<<std::endl;
    return fileList;
}

void Build::Init_build(const std::string projectPath)
{
    FileList=getProjectFiles(projectPath);
    // std::cout<<"all files be"<<std::endl;
}

std::vector<std::filesystem::path> Build::getFileList()
{
    return FileList;
}


