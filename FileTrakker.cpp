#include <fstream>
#include <exception>
#include <iostream>
#include <regex>
#include <format>
#include <chrono>
#include <sstream>
#include <iomanip>
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
    return content;
}

std::string FileTracker::ExtractSoucreeFileContenet(std::string content)
{
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

std::filesystem::file_time_type FileTracker::convertStringToFileTimeType(const std::string& dateTimeStr) 
{
    std::tm tm = {};
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    return std::filesystem::file_time_type::clock::from_sys(tp);
}

std::string FileTracker::logTimeFile_extractFilesNameAsString(std::string content)
{
    std::string filesName;

    std::regex TimeStamp("[0-9][0-9]|(:)|(-)|(.))*");
    std::regex space(" ");
    std::regex tabs("\t");


    filesName=std::regex_replace(content,TimeStamp,"");
    filesName=std::regex_replace(filesName,tabs,"");
    filesName=std::regex_replace(filesName,space,"");    

    return filesName;
}

std::string FileTracker::logHashFile_extractFliesNameAsString(std::string content)
{
    std::string filesName;

    std::regex Hash("[0-9][0-9]*");
    std::regex space(" ");
    std::regex tabs("\t");


    filesName=std::regex_replace(content,Hash,"");
    filesName=std::regex_replace(filesName,tabs,"");
    filesName=std::regex_replace(filesName,space,"");    

    return filesName;
}

std::string FileTracker::logTimeFile_extractTimeStampsAsString(std::string content)
{
    std::string timeStamps;

    std::regex fileName("[A-z].*\t");

    std::regex space(" ");
    std::regex tabs("\t");


    timeStamps=std::regex_replace(content,fileName,"");
    timeStamps=std::regex_replace(timeStamps,tabs,"");
    timeStamps=std::regex_replace(timeStamps,space,""); 

    return timeStamps;
}

std::string FileTracker::logHashFile_extractHashAsString(std::string content)
{
    std::string hashs;
    std::regex fileName("[A-z].*\t");
    std::regex space(" ");
    std::regex tabs("\t");

    hashs=std::regex_replace(content,fileName,"");
    hashs=std::regex_replace(hashs,tabs,"");
    hashs=std::regex_replace(hashs,space,"");
    return hashs;
}

void FileTracker::removeFile(const char * fFilePtr)
{
    if(remove(fFilePtr) == 0)
    {
        std::cout<<fFilePtr<<"was deleted successfuly."<<std::endl;
    }
    else
    {
        std::cerr<<"Error: failed to remove "<<fFilePtr<<std::endl;
    }
}

std::map<std::string,std::filesystem::file_time_type> FileTracker::generateTimeStampMap(std::string timeStampLogFile)
{
    std::filesystem::file_time_type temp;
    std::map<std::string,std::filesystem::file_time_type> timeStampMap;
    timeStampLogFile+="/FileListTimeStamp.txt";
    std::string content,filesName,timeStampStr;
    std::map<std::string,std::size_t> hashMap;
    content=readFileContent(timeStampLogFile);
   
    filesName=logTimeFile_extractFilesNameAsString(content);
    timeStampStr=logTimeFile_extractTimeStampsAsString(content);

    try
    {
        std::fstream myfile("filesName.txt",std::ios::in|std::ios::out|std::ios::app);
        myfile<<filesName;

        std::fstream mfile("Tstamps.txt",std::ios::in|std::ios::out|std::ios::app);
        mfile<<timeStampStr;
        std::string line;
        std::string hhash;
        
        myfile.seekg(0);
        mfile.seekg(0);

        while (std::getline(myfile,line)&&std::getline(mfile,hhash))
        {
            temp=convertStringToFileTimeType(hhash);
            timeStampMap.insert({line,temp});
        }
        
        myfile.close();
        mfile.close();

        const char * fNamePtr = "filesName.txt";
        const char * fTimePtr = "Tstamps.txt";
        removeFile(fNamePtr);
        removeFile(fTimePtr);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return timeStampMap;
}

std::map<std::string,std::size_t> FileTracker::generateHashMap(std::string hashLogFile)
{
    std::size_t tempHash;
    hashLogFile+="/fileList_hashs.txt";
    std::string content,filesName,hashs;
    std::map<std::string,std::size_t> hashMap;
    content=readFileContent(hashLogFile);

    filesName=logHashFile_extractFliesNameAsString(content);
    hashs=logHashFile_extractHashAsString(content);

    try
    {
        std::fstream myfile("filesName.txt",std::ios::in|std::ios::out|std::ios::app);
        myfile<<filesName;

        std::fstream mfile("hashs.txt",std::ios::in|std::ios::out|std::ios::app);
        mfile<<hashs;
        
        myfile.seekg(0);
        mfile.seekg(0);

        std::string fileNameLine;
        std::string hashLine;

        while (std::getline(myfile,fileNameLine)&&std::getline(mfile,hashLine))
        {
            std::stringstream sstream(hashLine);
            sstream >> tempHash;
            hashMap.insert({fileNameLine,tempHash});
        }
        myfile.close();
        mfile.close();
        const char * fNamePtr = "filesName.txt";
        const char * fHashPtr = "hashs.txt";
        removeFile(fNamePtr);
        removeFile(fHashPtr);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return hashMap;
}

std::vector<std::string> FileTracker::compareTimeStampLists(std::map<std::string,std::filesystem::file_time_type> timeListFromLog,std::map<std::string,std::filesystem::file_time_type> timeListGenerate)
{
    std::vector<std::string> fList;
    std::vector<std::string> fileListNeededBuild;
    for(auto file : timeListFromLog)
    {
        if(timeListFromLog.find(file.first)!=timeListGenerate.find(file.first))
        {
            fList.push_back(file.first);
        }
    }

    return fList;
}

std::vector<std::string> FileTracker::compareHashLists(std::vector<std::string> fList , std::map<std::string,std::size_t> hashMap)
{
    std::vector<std::string> UL;
    for(auto file : fList)
    {
        if(hashMap.find(file)->second!=generateHash(getfileContent(file)))
        {
            UL.push_back(file);
        }
    }
    return UL;
}


FileTracker::FileTracker(std::vector<std::filesystem::path> filesList)
{
    projectFilesList=filesList;
}

std::map<std::string,std::size_t> FileTracker::generateFilesHash(std::vector<std::filesystem::path> filesList)
{
    std::string fileContent;
    std::map<std::string,std::size_t> FilesHashListCopy;

    for (auto file :filesList)
    {
        auto fileNameString=file.c_str();
        fileContent = readFileContent(fileNameString);
        fileContent = ExtractSoucreeFileContenet(fileContent);
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

std::vector<std::filesystem::path> FileTracker::getUpdatedFilesList(std::string projectPath)
{
    std::vector<std::filesystem::path> fileList;
    std::vector<std::string> updatedFileList();
    generateHashMap(projectPath);
    compareTimeStampLists(generateTimeStampMap(projectPath),generateFilesTimeStamp(fileList));

    return fileList;
}

std::string FileTracker::getfileContent(std::string fileName)
{
    std::string content;
    for(auto file : projectFilesList)
    {
        if(fileName==file.filename().string())
        {
            content=readFileContent(file.c_str());
            content=ExtractSoucreeFileContenet(content);
            return fileName;
        }
    }
}