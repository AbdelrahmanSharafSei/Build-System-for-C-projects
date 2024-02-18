#include <iostream>
#include <filesystem>
#include "Build.h"

namespace fs = std::filesystem;

int main(int argc,char **argv)
{
    int r;
    Build x;
    x.Init_build("E:/25_Impl/85_Release");

    std::cin>>r;
    return 0;
}
