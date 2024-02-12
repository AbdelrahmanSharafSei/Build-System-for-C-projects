#include <iostream>
#include <filesystem>
#include "Build.h"

namespace fs = std::filesystem;

int main(int argc,char **argv)
{
    int r;
    Build x;
    x.Init_build("C:/Users/AbdelrahmanSharaf");
    auto logs=x.getFileList();
    for (auto i: logs)
    {
        std::cout<<i.filename()<<std::endl;
    }
    
    std::cin>>r;
    return 0;
}
