#include <boost/shared_ptr.hpp>
#include <boost/dll.hpp>
#include <iostream>
#include <sstream>

#include "depengine/Depengine.hpp"
#include "ActionAdapter.hpp"
#include "ShellAction.hpp"


namespace treet
{
using namespace boost::dll;
using namespace depengine;
using namespace std;


const char* kSetupFuncAlias = "setup";
const char* kEngineAlias = "engine";
const char* kFileName = "build";
const char* kCpp = ".cpp";
const char* kSo = ".so";

const char* kFlags = "-undefined dynamic_lookup "
                     "-std=c++14 "
                     "-fPIC "
                     "-I. ";


string buildCommand(const string& fileName)
{
    stringstream command;
    command << "g++ " << kFlags << fileName << kCpp << " -o " << fileName
            << kSo;
    return command.str();
}


auto scriptEngine(
    const string& scriptLib,
    const string& setupFuncAlias,
    const string& scriptAlias
)
{
    cout << "Loading script library." << endl;
    const auto setupFunc = import_alias<void()>(scriptLib, setupFuncAlias);
    cout << "Running script." << endl;
    setupFunc();

    return import_alias<Depengine>(scriptLib, scriptAlias);
}


} // namespace treet


int main()
{
    using namespace treet;
    const auto kScriptEngine = "scriptEngine";
    const auto thisBinary = program_location();
    const auto scriptFile = string(kFileName) + kCpp;
    const auto scriptLib = string(kFileName) + kSo;

    Depengine bootstrapper;

    // Build the script
    bootstrapper.rule(
        scriptLib, {scriptFile, thisBinary.c_str()},
        ShellAction({buildCommand(kFileName)}));

    // Load the script
    bootstrapper.rule(
        kScriptEngine, {scriptLib}, ActionAdapter(
            scriptEngine, scriptLib, kSetupFuncAlias, kEngineAlias
        ));

    bootstrapper.rule(kScriptEngine).run();


    auto engine = bootstrapper.product<
        boost::shared_ptr<Depengine>
    >(kScriptEngine);

    engine->rule("output").run();
}
