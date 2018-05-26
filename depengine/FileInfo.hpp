#pragma once

#include <sys/stat.h>
#include <sstream>
#include <string>

using std::string;


struct FileInfo {
    const bool exists;
    const time_t lastChange;
    static FileInfo get(const string& path);
};
