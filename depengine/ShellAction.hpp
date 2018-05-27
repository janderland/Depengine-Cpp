#pragma once

#include "DepException.hpp"
#include <iostream>
#include <string>


namespace depengine {
using std::string;
using std::cout;
using std::endl;


class ShellAction {
private:
    string _command;

public:
    ShellAction(string command):
        _command(move(command)) { }

    void operator()() const {
        cout << "Executing command \"" << _command
            << "\"." << endl;

        FILE* pipe = popen("bash", "w");
        if (pipe) {
            fprintf(pipe, "%s\n", _command.c_str());
            if (pclose(pipe) != 0) {
                throw DepException("Command failed on exit.");
            }
        }
        else {
            throw DepException("Failed to start shell.");
        }
    }
};


} // namespace depengine
