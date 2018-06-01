#include <boost/dll/alias.hpp>
#include <boost/any.hpp>

#include "depengine/RuleDetails.hpp"
#include "depengine/Registry.hpp"
#include "depengine/Rule.hpp"
#include "ShellAction.hpp"


#define TREET_ENTRY(FUNC) \
    BOOST_DLL_ALIAS(FUNC, build)


#define TREET_NO_PRODUCT \
    return boost::any();


namespace treet {

namespace tools {


depengine::Registry& getRegistry() {
    static depengine::Registry registry;
    return registry;
}


void rule(std::string name,
        std::vector<std::string> dependencies,
        std::vector<std::string> commands) {
    getRegistry().createRule(
        depengine::RuleDetails(
            name, dependencies,
            ShellAction(commands)
        )
    );
}


void rule(std::string name, std::vector<std::string> commands) {
    getRegistry().createRule(
        depengine::RuleDetails(
            name, { },
            ShellAction(commands)
        )
    );
}


void rule(std::string name,
        std::vector<std::string> dependencies,
        depengine::Action action) {
    getRegistry().createRule(
        depengine::RuleDetails(
            name, dependencies,
            action
        )
    );
}


void rule(std::string name, depengine::Action action) {
    getRegistry().createRule(
        depengine::RuleDetails(
            name, { },
            action
        )
    );
}


} // namespace tools

} // namespace treet


BOOST_DLL_ALIAS(treet::tools::getRegistry, getRegistry)
