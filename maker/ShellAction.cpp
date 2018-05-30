#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "depengine/DepException.hpp"
#include "depengine/Var.hpp"
#include "ShellAction.hpp"


namespace maker {
using depengine::DepException;
using boost::algorithm::join;
using boost::replace_all;
using std::stringstream;
using std::vector;
using std::string;
using std::cout;
using std::endl;


string replaceCodes(
        const string& command,
        const string& product,
        const vector<string>& dependencies) {
    std::string newCommand = command;

    replace_all(newCommand, "$p", product);

    if (dependencies.size() > 0) {
        replace_all(newCommand, "$d", dependencies[0]);
    }
    else if (newCommand.find("$d") != string::npos) {
        stringstream message;
        message
            << "Command \"" << command << "\" "
               "has a \"$d\" but this rule has "
               "no dependencies.";
        throw DepException(message.str());
    }

    if (dependencies.size() > 0) {
        replace_all(newCommand, "$D", join(dependencies, ", "));
    }
    else if (newCommand.find("$D") != string::npos) {
        stringstream message;
        message
            << "Command \"" << command << "\" "
               "has a \"$D\" but this rule has "
               "no dependencise.";
        throw DepException(message.str());
    }

    return newCommand;
}


ShellAction::ShellAction(const vector<string>& commands):
    _commands(commands) { }


void ShellAction::operator()(
        const string& product,
        const vector<string>& dependencies) const {
    FILE* pipe = popen("bash", "w");
    if (pipe) {
        for (REF cmdPattern : _commands) {
            VAL command
                = replaceCodes(cmdPattern,
                               product,
                               dependencies);

            cout
                << "Piping command \"" << command
                << "\"." << endl;

            fprintf(pipe, "%s\n", command.c_str());
        }
        if (pclose(pipe) != 0) {
            throw DepException("One or more commands failed.");
        }
    }
    else {
        throw DepException("Failed to start shell.");
    }
}


} // namespace depengine
