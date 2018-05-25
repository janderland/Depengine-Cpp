#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "DepException.hpp"
#include "RuleDetails.hpp"
#include "Var.hpp"

using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;


RuleDetails::RuleDetails(
        string product,
        string command,
        vector<string> dependencies):
    _product(move(product)),
    _command(move(command)),
    _dependencies(move(dependencies)) { }


const string& RuleDetails::getProduct() const {
    return _product;
}


const vector<string>& RuleDetails::getDependencies() const {
    return _dependencies;
}


struct FileInfo {
    const bool exists;
    const time_t lastChange;

    static FileInfo get(const string& path) {
        struct stat info;
        if (stat(path.c_str(), &info)) {
            if (errno == ENOENT) {
                return { false, 0 };
            }
            else {
                stringstream message;
                message << "Failed to get file info for \""
                    << path << "\".";
                throw DepException(message.str());
            }
        }
        else {
            return { true, info.st_mtime };
        }
    }
};


bool RuleDetails::mustExecute() const {
    cout << "Checking \"" << _product
        << "\"." << endl;

    VAL prodFile = FileInfo::get(_product);
    if (prodFile.exists)
    {
        cout << "Product exists." << endl;
        for (REF dependency : _dependencies) {
            VAL depFile = FileInfo::get(dependency);
            if (depFile.exists) {
                if (depFile.lastChange > prodFile.lastChange) {
                    cout << "Dependency \"" << dependency
                        << "\" is newer than product."
                        << endl;
                    return true;
                }
            }
            else {
                stringstream message;
                message << "Dependency \"" << dependency
                    << "\" doesn't exist." << endl;
                throw DepException(message.str());
            }
        }
        return false;
    }
    else {
        cout << "Product doesn't exist." << endl;
        return true;
    }
}


void RuleDetails::execute() const {
    cout << "Executing command \"" << _command
        << "\"." << endl;

    FILE* pipe = popen("bash", "w");
    if (pipe) {
        fprintf(pipe, "%s\n", _command.c_str());
        if (pclose(pipe) != 0) {
            cerr << "Command failed on exit."
                << endl;
        }
    }
    else {
        cerr << "Command failed on start."
            << endl;
    }
}
