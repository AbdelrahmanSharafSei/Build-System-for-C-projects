#ifndef FILETRAKKER_H
#define FILETRAKKER_H

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>

typedef std::map<std::string,std::size_t> MHasH;

class FileTracker
{
    private:
    
        std::vector<std::filesystem::path> projectFilesList;

        std::string getfileContent(std::string fileName);
        
        std::string readFileContent(std::filesystem::path fpath);
        std::string ExtractSoucreeFileContenet(std::string content);
        std::size_t generateHash(const std::string& data);

        void removeFile(const char * fFilePtr);

        std::string logHashFile_extractHashAsString(std::string content);
        std::string logHashFile_extractFliesNameAsString(std::string content);

        std::string logTimeFile_extractTimeStampsAsString(std::string content);
        std::string logTimeFile_extractFilesNameAsString(std::string content);

        std::map<std::string,std::size_t> generateHashMap(std::string hashFileLog);
        std::map<std::string,std::filesystem::file_time_type> generateTimeStampMap(std::string timeStampLogFile);

        std::filesystem::file_time_type convertStringToFileTimeType(const std::string& dateTimeStr);

        std::vector<std::string> compareTimeStampLists(std::map<std::string,std::filesystem::file_time_type> timeListFromLog,std::map<std::string,std::filesystem::file_time_type> timeListGenerate);
        std::vector<std::string> compareHashLists(std::vector<std::string> fList ,std::map<std::string,std::size_t> Hashmap);
    
    public:

        FileTracker(std::vector<std::filesystem::path> fileslist);

        void logHashToTxtFile(std::string FilePath,std::map<std::string,std::size_t> FilesHashListCoyp);
        void logTimeStampToTxtFile(std::string FilePath,std::map<std::string,std::filesystem::file_time_type> FilesTimeStampListCoyp);

        std::map<std::string,std::filesystem::file_time_type> generateFilesTimeStamp(std::vector<std::filesystem::path> filesList);
        std::map<std::string,std::size_t> generateFilesHash(std::vector<std::filesystem::path> filesList);
                
        void printtHashs();

        std::vector<std::filesystem::path> getUpdatedFilesList(std::string projectPath);
};



#endif