#include <boost/dll.hpp>
#include <functional>
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
using boost::any_cast;
using namespace std;


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


function<Registry&()> loadScript(
        const string& scriptLib, const string& funcName) {
    cout << "Loading script library." << endl;
    REF buildFunc = import_alias<void()>(
        scriptLib, funcName
    );
    cout << "Running script." << endl;
    buildFunc();

    return import_alias<Registry&()>(
        scriptLib, "getRegistry"
    );
}


} // namespace treet


int main() {
    using namespace depengine;
    using namespace treet;

    VAL kLoadScript = "getRegistry";
    VAL thisBinary = program_location();
    VAL scriptFile = kFileName + kCpp;
    VAL scriptLib = kFileName + kSo;

    Registry registry;

    // Build the script
    registry.createRule(RuleDetails(
        scriptLib, { scriptFile, thisBinary.c_str() },
        ShellAction({ buildCommand(kFileName) })));

    // Load the script
    registry.createRule(RuleDetails(
        kLoadScript, { scriptLib }, [&] (auto, auto) {
            return any(loadScript(scriptLib, kFuncName));
        }));

    registry.getRule(kLoadScript).run();
    any& getRegistry = registry.getProducts()[kLoadScript];
    auto& otherReg = any_cast<function<Registry&()>>(getRegistry)();
    otherReg.getRule("output").run();
}
