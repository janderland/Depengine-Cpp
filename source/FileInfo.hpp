#pragma once

#include <sys/stat.h>
#include <sstream>
#include <string>

using std::string;


struct FileInfo {
    const bool _exists;
    const time_t _lastChange;
    static FileInfo get(const string& path);
};
