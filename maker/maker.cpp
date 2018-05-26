#include <boost/dll.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "depengine/RuleDetails.hpp"
#include "depengine/Registry.hpp"
#include "depengine/Rule.hpp"
#include "depengine/Var.hpp"
#include "MakException.hpp"

using std::stringstream;
using std::string;
using std::cout;
using std::endl;


const string kName = "build";
const string kCpp = ".cpp";
const string kSo = ".so";

const string kFlags = "-undefined dynamic_lookup "
                      "-std=c++14 "
                      "-fPIC "
                      "-I. ";


string buildCommand(const string& name) {
    stringstream command;
    command
        << "g++ " << kFlags << name << kCpp
        << " -o " << name << kSo;
    return command.str();
}


void buildInstructions(const string& name) {
    VAL output = name + kSo;
    VAL source = name + kCpp;

    Registry registry;
    registry.createRule(
        RuleDetails(
            output,
            buildCommand(name),
            { source }
        )
    );
    registry.getRule(output).run();
}


void loadInstructions(const string& name) {
    cout << "Loading build instructions." << endl;
    REF buildFunc = boost::dll::import_alias<void()>(
            name + kSo, name
    );
    cout << "Running build." << endl;
    buildFunc();
}


int main() {
    buildInstructions(kName);
    loadInstructions(kName);
}
