#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "DepException.hpp"
#include "ShellAction.hpp"
#include "Var.hpp"


namespace depengine {
using boost::algorithm::join;
using boost::replace_all;
using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;


string ShellAction::replaceCodes(
        const string& product,
        const vector<string>& dependencies) const {
    string command(_command);
    replace_all(command, "$p", product);


    if (dependencies.size() > 0) {
        replace_all(command, "$d", dependencies[0]);
    }
    else if (command.find("$d") != string::npos) {
        stringstream message;
        message
            << "Command \"" << _command << "\" "
               "has a \"$d\" but this rule has "
               "no dependencise.";
        throw DepException(message.str());
    }


    if (dependencies.size() > 0) {
        replace_all(command, "$D", join(dependencies, ", "));
    }
    else if (command.find("$D") != string::npos) {
        stringstream message;
        message
            << "Command \"" << _command << "\" "
               "has a \"$D\" but this rule has "
               "no dependencise.";
        throw DepException(message.str());
    }

    return command;
}


ShellAction::ShellAction(const string& command):
    _command(command) { }


void ShellAction::operator()(const string& product,
        const vector<string>& dependencies) const {
    VAL command = replaceCodes(product, dependencies);

    cout << "Executing command \"" << command
        << "\"." << endl;

    FILE* pipe = popen("bash", "w");
    if (pipe) {
        fprintf(pipe, "%s\n", command.c_str());
        if (pclose(pipe) != 0) {
            throw DepException("Command failed on exit.");
        }
    }
    else {
        throw DepException("Failed to start shell.");
    }
}


} // namespace depengine
