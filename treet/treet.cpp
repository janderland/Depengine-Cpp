#include <boost/shared_ptr.hpp>
#include <boost/dll.hpp>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "depengine/Depengine.hpp"
#include "ShellAction.hpp"


namespace treet {
using boost::dll::program_location;
using boost::dll::import_alias;
using namespace depengine;
using namespace std;


const string kGetEngineFuncName = "engine";
const string kSetupFuncName = "setup";
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


auto loadScript(
        const string& scriptLib,
        const string& setupFuncName,
        const string& scriptEngineName) {
    cout << "Loading script library." << endl;
    REF setupFunc = import_alias<void()>(
        scriptLib, setupFuncName
    );
    cout << "Running script." << endl;
    setupFunc();

    return import_alias<Depengine>(
        scriptLib, scriptEngineName
    );
}


} // namespace treet


int main() {
    using namespace treet;
    VAL kLoadScript = "loadScript";
    VAL thisBinary = program_location();
    VAL scriptFile = kFileName + kCpp;
    VAL scriptLib = kFileName + kSo;

    Depengine boostrapper;

    // Build the script
    boostrapper.createRule(
        scriptLib,
        { scriptFile, thisBinary.c_str() },
        ShellAction({
            buildCommand(kFileName)
        }));

    // Load the script
    boostrapper.createRule(
        kLoadScript,
        { scriptLib },
        [&] (auto, auto) {
            return loadScript(
                    scriptLib,
                    kSetupFuncName,
                    kGetEngineFuncName);
        });

    boostrapper.getRule(kLoadScript).run();


    MUTABLE_VAL scriptEngine =
        boostrapper.getProduct<
            boost::shared_ptr<Depengine>
        >(kLoadScript);

    scriptEngine->getRule("output").run();
}
