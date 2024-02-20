#include <fstream>
#include <exception>
#include <iostream>
#include <regex>
#include <format>
#include <chrono>
#include "FileTrakker.h"

using namespace std::chrono_literals;


std::string FileTracker::readFileContent(std::filesystem::path fpath)
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

std::size_t FileTracker::generateHash(const std::string& data) 
{
    std::hash<std::string> hasher;
    return hasher(data);
}



FileTracker::FileTracker(std::vector<std::filesystem::path> filesList)
{
    filesList=filesList;
}


std::map<std::string,std::size_t> FileTracker::generateFilesHash(std::vector<std::filesystem::path> filesList)
{
    std::string fileContent;
    std::map<std::string,std::size_t> FilesHashListCopy;
    for (auto file :filesList)
    {
        auto fileNameString=file.c_str();
        fileContent = readFileContent(fileNameString);
        FilesHashListCopy.insert({file.filename().string(),generateHash(fileContent)});
    }
    return FilesHashListCopy;
}

std::map<std::string,std::filesystem::file_time_type> FileTracker::generateFilesTimeStamp(std::vector<std::filesystem::path> filesList)
{
    std::map<std::string,std::filesystem::file_time_type> FilesTimeStampListCopy;
    for(auto file :filesList)
    {
        std::filesystem::file_time_type ftime = std::filesystem::last_write_time(file);
        FilesTimeStampListCopy.insert({file.filename().string(),ftime});
    }
    return FilesTimeStampListCopy;   
}


void FileTracker::logHashToTxtFile(std::string FilePath,std::map<std::string,std::size_t> FilesHashListCoyp)
{
    std::ofstream myfile(FilePath+"/fileList_hashs.txt");
    if (!myfile.is_open())
    {
        throw std::runtime_error("Failed to open file: fileList_hashs.txt");
    }
    else
    {
        for(auto file :FilesHashListCoyp)
        {   
            myfile.width(37);
            myfile<<file.first<<"\t\t"<<file.second<<"\n";
        }   
    }
    myfile.close();
}

void FileTracker::logTimeStampToTxtFile(std::string FilePath,std::map<std::string,std::filesystem::file_time_type> FilesTimeStampListCoyp)
{
    std::ofstream myfile(FilePath+"/FileListTimeStamp.txt");
    if (!myfile.is_open())
    {
        throw std::runtime_error("Failed to open file: fileList_hashs.txt");
    }
    else
    {
        for(auto file :FilesTimeStampListCoyp)
        {   
            myfile.width(37);
            myfile<<file.first<<"\t\t"<<file.second<<"\n";
        }   
    }
    myfile.close();
}


void FileTracker::printtHashs()
{
    for(auto file :generateFilesHash(projectFilesList))
    {
        std::cout.width(37);
        std::cout<<file.first<<"  "<<file.second<<std::endl;
    }
}