#include <boost/dll/alias.hpp>
#include <boost/any.hpp>

#include "depengine/Depengine.hpp"
#include "ShellAction.hpp"


#define TREET_SETUP(FUNC) \
    BOOST_DLL_ALIAS(FUNC, setup)


#define TREET_NO_PRODUCT \
    return boost::any();


namespace treet
{

namespace tools
{


depengine::Depengine engine;


void rule(
    const std::string& name,
    const std::vector<std::string>& dependencies,
    const std::vector<std::string>& commands
)
{
    engine.rule(name, dependencies, ShellAction(commands));
}


void rule(
    const std::string& name,
    const std::vector<std::string>& commands
)
{
    engine.rule(name, { }, ShellAction(commands));
}


void rule(
    const std::string& name,
    const std::vector<std::string>& dependencies,
    const depengine::Action& action
)
{
    engine.rule(name, dependencies, action);
}


void rule(
    const std::string& name,
    const depengine::Action& action
)
{
    engine.rule(name, { }, action);
}


} // namespace tools

} // namespace treet


BOOST_DLL_ALIAS(treet::tools::engine, engine)
