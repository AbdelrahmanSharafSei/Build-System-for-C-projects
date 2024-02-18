#ifndef FILETRAKKER_H
#define FILETRAKKER_H

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <filesystem>

class FileTrakker
{
    private:
        std::map<std::string,std::size_t> filesLog;
        std::string readFileContent(std::filesystem::path fpath);
        std::size_t generateHash(const std::string& data);
    public:
        FileTrakker(std::vector<std::filesystem::path> fileslist);
        void printtHashs();

};


#endif