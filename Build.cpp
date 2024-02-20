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

bool Build::isInitProjectFilesGenerated(const std::string projectPath)
{
    std::string fFileListlog="fileList_hashs.txt";
    std::string fFileListTimeStamp="FileListTimeStamp.txt";
    std::string Temp;
    bool timeFilecond,hashFileCond;
    for(auto const& dir_entry : std::filesystem::directory_iterator(projectPath))
    {
        Temp=dir_entry.path().filename().string();

        if(fFileListlog==Temp)
        {
            hashFileCond=true;
        }
        else if(fFileListTimeStamp==Temp)
        {
            timeFilecond=true;
        }
        else
        {

        }
    }
    if (timeFilecond&&hashFileCond)
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

Build::Build(const std::string projectPath)
{
    FileList=getProjectFiles(projectPath);
    FileTracker FT(FileList);
    
    if(isInitProjectFilesGenerated(projectPath))
    {
        std::cout<<"already Init"<<std::endl;
        // read the two files
        // compare stamp file with current stamp map, then output list for changed files
        // calculate hash for the list, then compare, then output the changed files
    }
    else
    {
        FT.logHashToTxtFile(projectPath,FT.generateFilesHash(FileList));
        FT.logTimeStampToTxtFile(projectPath,FT.generateFilesTimeStamp(FileList));  
        Staged=true;
    }
}

std::vector<std::filesystem::path> Build::getFileList()
{
    return FileList;
}


