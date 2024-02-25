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
        
        std::string readFileContent(std::filesystem::path fpath);
        std::string ExtractSoucreeFileContenet(std::string content);
        std::size_t generateHash(const std::string& data);

        std::map<std::string,std::size_t> generateHashMap(std::string hashFileLog);
        std::map<std::string,std::filesystem::file_time_type> generateTimeStampMap(std::string timeStampLogFile);

    public:

        FileTracker(std::vector<std::filesystem::path> fileslist);

        void logHashToTxtFile(std::string FilePath,std::map<std::string,std::size_t> FilesHashListCoyp);
        void logTimeStampToTxtFile(std::string FilePath,std::map<std::string,std::filesystem::file_time_type> FilesTimeStampListCoyp);

        std::map<std::string,std::filesystem::file_time_type> generateFilesTimeStamp(std::vector<std::filesystem::path> filesList);
        std::map<std::string,std::size_t> generateFilesHash(std::vector<std::filesystem::path> filesList);
                
        void printtHashs();

        std::vector<std::filesystem::path> getUpdatedFilesList();
};


#endif