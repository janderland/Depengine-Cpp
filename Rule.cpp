#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "Rule.hpp"
#include "DepException.hpp"


Rule::Rule(const std::string& product, const std::string& command,
        std::vector<Dependency>&& dependencies):
    _product(product),
    _command(command),
    _dependencies(dependencies) { }


struct FileInfo {
    const bool exists;
    const time_t lastChange;
};


FileInfo getFileInfo(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info)) {
        if (errno == ENOENT) {
            return { false, 0 };
        }
        else {
            std::stringstream message;
            message << "Failed to get file info for \""
                << path << "\".";
            throw DepException(message.str());
        }
    }
    else {
        return { true, info.st_mtime };
    }
}


bool mustExecute(const std::string& product,
        const std::vector<Dependency>& dependencies) {
    std::cout << "Checking \"" << product  << "\"." << std::endl;

    const auto prodFile = getFileInfo(product);
    if (prodFile.exists)
    {
        std::cout << "Product exists." << std::endl;
        for (const auto& dependency : dependencies) {
            const auto depPath = dependency.product();
            const auto depFile = getFileInfo(depPath);
            if (depFile.exists) {
                if (depFile.lastChange > prodFile.lastChange) {
                    std::cout << "Dependency \"" << depPath
                        << "\" is newer than product." << std::endl;
                    return true;
                }
            }
            else {
                std::stringstream message;
                message << "Dependency \"" << depPath
                    << "\" doesn't exist." << std::endl;
                throw DepException(message.str());
            }
        }
        return false;
    }
    else {
        std::cout << "Product doesn't exist." << std::endl;
        return true;
    }
}


void execute(const std::string& command) {
    std::cout << "Executing command \"" << command
        << "\"." << std::endl;

    FILE* pipe = popen("bash", "w");
    if (pipe) {
        fprintf(pipe, "%s\n", command.c_str());
        if (pclose(pipe) != 0) {
            std::cerr << "Command failed on exit."
                << std::endl;
        }
    }
    else {
        std::cerr << "Command failed on start."
            << std::endl;
    }
}


void run(const std::vector<Dependency>& dependencies) {
    for (const auto& dependency : dependencies) {
        dependency.get().run();
    }
}


void Rule::run() const {
    ::run(_dependencies);
    if (mustExecute(_product, _dependencies)) {
        execute(_command);
    }
}
