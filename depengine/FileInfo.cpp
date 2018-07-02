#include <sys/stat.h>
#include <sstream>

#include "DepException.hpp"
#include "FileInfo.hpp"


namespace depengine
{


    FileInfo FileInfo::get(const string& path)
    {
        struct stat info;
        if (stat(path.c_str(), &info)) {
            if (errno == ENOENT) {
                return {false, 0};
            }
            else {
                stringstream message;
                message << "Failed to get file info for \"" << path << "\".";
                throw DepException(message.str());
            }
        }
        else {
            return {true, info.st_mtime};
        }
    }


} // namespace depengine
