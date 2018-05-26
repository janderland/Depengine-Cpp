#pragma once

#include <sys/stat.h>
#include <sstream>
#include <string>


namespace depengine {
using std::string;


struct FileInfo {
    const bool exists;
    const time_t lastChange;
    static FileInfo get(const string& path);
};


} // namespace depengine
