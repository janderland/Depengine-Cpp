#include <sys/stat.h>
#include <iostream>
#include <cstdio>

#include "Rule.hpp"
#include "Registry.hpp"
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


FileInfo getInfo(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info)) {
        if (errno == ENOENT) {
            return { false, 0 };
        }
        else {
            throw DepException("Failed to check product.");
        }
    }
    else {
        return { true, info.st_mtime };
    }
}


bool mustExecute(const std::string& product) {
    std::cout << "Checking \"" << product << std::endl;

    const auto thisInfo = getInfo(product);
    if (thisInfo.exists)
    {
        std::cout << "Product exists." << std::endl;
        return false;
    }
    else {
        std::cout << "Product doesn't exist." << std::endl;
        return true;
    }
}


void execute(const std::string& command) {
    std::cout << "Executing command \"" << command
        << "\"..." << std::endl;

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
    if (mustExecute(_product)) {
        execute(_command);
    }
}
