#include <fstream>
#include <exception>
#include <iostream>
#include <regex>
#include "FileTrakker.h"


std::string FileTrakker::readFileContent(std::filesystem::path fpath)
{
    auto filename=fpath.c_str();
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) 
    {
        throw std::runtime_error("Failed to open file: ");
    }
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
        std::regex newline("( |\\n)");
        std::regex multiplieComment("(//[^\n]*$|/(?!\\\\)\\*[\\s\\S]*?\\*(?!\\\\)/)|(//.*\\n)");

        content=std::regex_replace(content,multiplieComment,"");
        content=std::regex_replace(content,newline,"");
    return content;
}

std::size_t FileTrakker::generateHash(const std::string& data) 
{
    std::hash<std::string> hasher;
    return hasher(data);
}

FileTrakker::FileTrakker(std::vector<std::filesystem::path> filesList)
{
    std::string fileContent;
    for (auto count :filesList)
    {
        auto x=count.c_str();
        fileContent=readFileContent(x);
        filesLog.insert({count.filename().string(),generateHash(fileContent)});
    }
    
}

void FileTrakker::printtHashs()
{
    for(auto count :filesLog)
    {
        std::cout<<count.first<<" "<<count.second<<std::endl;
    }
}