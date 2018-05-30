#include <boost/dll.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "depengine/RuleDetails.hpp"
#include "depengine/Registry.hpp"
#include "depengine/Rule.hpp"
#include "depengine/Var.hpp"
#include "ShellAction.hpp"

using boost::dll::program_location;
using boost::dll::import_alias;
using std::stringstream;
using std::string;
using std::cout;
using std::endl;


namespace treet {


const string kFuncName = "build";
const string kFileName = "build";
const string kCpp = ".cpp";
const string kSo = ".so";

const string kFlags = "-undefined dynamic_lookup "
                      "-std=c++14 "
                      "-fPIC "
                      "-I. ";


string buildCommand(const string& fileName) {
    stringstream command;
    command
        << "g++ " << kFlags << fileName << kCpp
        << " -o " << fileName << kSo;
    return command.str();
}


void loadScript(const string& scriptLib, const string& funcName) {
    cout << "Loading script library." << endl;
    REF buildFunc = import_alias<void()>(
            scriptLib, funcName
    );
    cout << "Running script." << endl;
    buildFunc();
}


} // namespace treet


int main() {
    using namespace depengine;
    using namespace treet;

    VAL kLoadScript = "loadScript";
    VAL thisBinary = program_location();
    VAL scriptFile = kFileName + kCpp;
    VAL scriptLib = kFileName + kSo;

    Registry registry;
    registry.createRule(
        RuleDetails( // Build the script
            scriptLib, { scriptFile, thisBinary.c_str() },
            ShellAction({ buildCommand(kFileName) })
        )
    );
    registry.createRule(
        RuleDetails( // Load the script
            kLoadScript, { scriptLib },
            [&](const string&, const vector<string>&) {
                loadScript(scriptLib, kFuncName);
            }
        )
    );
    registry.getRule(kLoadScript).run();
}
