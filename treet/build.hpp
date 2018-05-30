#include "depengine/RuleDetails.hpp"
#include "depengine/Registry.hpp"
#include <boost/dll/alias.hpp>
#include "depengine/Rule.hpp"
#include "ShellAction.hpp"


#define MAKER_ENTRY(FUNC) \
    BOOST_DLL_ALIAS(FUNC, build)


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


void run(std::string name) {
    getRegistry().getRule(name).run();
}


} // namespace tools
} // namespace treet
