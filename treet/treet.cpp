#include <boost/shared_ptr.hpp>
#include <boost/dll.hpp>
#include <iostream>
#include <sstream>

#include "depengine/Depengine.hpp"
#include "ShellAction.hpp"


namespace treet
{
using namespace boost::dll;
using namespace depengine;
using namespace std;


const char* kGetEngineFuncName = "engine";
const char* kSetupFuncName = "setup";
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


auto loadScript(
    const string& scriptLib,
    const string& setupFuncName,
    const string& scriptEngineName
)
{
    cout << "Loading script library." << endl;
    const auto& setupFunc = import_alias<void()>(scriptLib, setupFuncName);
    cout << "Running script." << endl;
    setupFunc();

    return import_alias<Depengine>(scriptLib, scriptEngineName);
}


} // namespace treet


int main()
{
    using namespace treet;
    const auto kLoadScript = "loadScript";
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
        kLoadScript, {scriptLib}, [&](
            auto,
            auto
        ) {
            return loadScript(scriptLib, kSetupFuncName, kGetEngineFuncName);
        }
    );

    bootstrapper.rule(kLoadScript).run();


    auto scriptEngine = bootstrapper.product<
        boost::shared_ptr<Depengine>
    >(kLoadScript);

    scriptEngine->rule("output").run();
}
