#include <boost/dll.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "depengine/RuleDetails.hpp"
#include "depengine/ShellAction.hpp"
#include "depengine/Registry.hpp"
#include "depengine/Rule.hpp"
#include "depengine/Var.hpp"

using std::stringstream;
using std::string;
using std::cout;
using std::endl;


namespace maker {


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


void load(const string& fileName, const string& funcName) {
    cout << "Loading build instructions." << endl;
    REF buildFunc = boost::dll::import_alias<void()>(
            fileName + kSo, funcName
    );
    cout << "Running build." << endl;
    buildFunc();
}


} // namespace maker


int main() {
    using namespace depengine;
    using namespace maker;

    VAL source = kFileName + kCpp;
    VAL output = kFileName + kSo;
    VAL ruleName = "load";

    Registry registry;
    registry.createRule(
        RuleDetails(
            output, { source },
            ShellAction(buildCommand(kFileName))
        )
    );
    registry.createRule(
        RuleDetails(
            ruleName, { output },
            [&]() { load(kFileName, kFuncName); }
        )
    );
    registry.getRule(ruleName).run();
}
