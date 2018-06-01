#pragma once

#include <string>


namespace depengine {
using namespace std;


struct FileInfo {
    const bool exists;
    const time_t lastChange;
    static FileInfo get(const string& path);
};


} // namespace depengine
