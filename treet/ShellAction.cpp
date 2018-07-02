#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "depengine/DepException.hpp"
#include "depengine/Var.hpp"
#include "ShellAction.hpp"


namespace treet
{
    using namespace boost::algorithm;
    using namespace depengine;
    using namespace boost;
    using namespace std;


    string replaceCodes(
        const string& command,
        const string& product,
        const vector<string>& dependencies
    )
    {
        auto replaceSymbol = [&](
            auto symbol,
            auto replace
        ) {
            if (dependencies.size() > 0) {
                replace();
            }
            else {
                stringstream message;
                message << "Command \"" << command << "\" has a \"" << symbol
                        << "\" but this rule has no dependencies.";
                throw DepException(message.str());
            }
        };


        std::string newCommand = command;
        replace_all(newCommand, "$p", product);

        replaceSymbol(
            "$d", [&] {
                replace_all(newCommand, "$d", dependencies[0]);
            }
        );

        replaceSymbol(
            "$D", [&] {
                replace_all(newCommand, "$D", join(dependencies, " "));
            }
        );

        return newCommand;
    }


    ShellAction::ShellAction(
        const vector<string>& commands
    ):
        _commands(commands)
    {
    }


    any ShellAction::operator()(
        const string& product,
        const vector<string>& dependencies
    ) const
    {
        cout << "Opening shell for commands..." << endl;
        FILE* pipe = popen("bash", "w");

        if (pipe) {
            for (REF cmdPattern : _commands) {
                VAL command = replaceCodes(cmdPattern, product, dependencies);
                fprintf(pipe, "echo \"\\\"%s\\\"\"\n", string(command).c_str());
                fprintf(pipe, "%s\n", command.c_str());
            }

            if (pclose(pipe) != 0) {
                throw DepException("One or more commands failed.");
            }
            cout << "Shell closed." << endl;
        }
        else {
            throw DepException("Failed to start shell.");
        }

        return any();
    }


} // namespace treet
