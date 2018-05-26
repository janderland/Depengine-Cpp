#include <boost/dll/alias.hpp>

#include "depengine/RuleDetails.hpp"
#include "depengine/Registry.hpp"
#include "depengine/Rule.hpp"


#define MAKER_ENTRY(FUNC) \
    BOOST_DLL_ALIAS(FUNC, build)


namespace maker {
namespace tools {


depengine::Registry& getRegistry() {
    static depengine::Registry registry;
    return registry;
}


void rule(std::string name, std::vector<std::string> dependencies, std::string command) {
    getRegistry().createRule(depengine::RuleDetails(name, command, dependencies));
}


void rule(std::string name, std::string command) {
    getRegistry().createRule(depengine::RuleDetails(name, command));
}


void run(std::string name) {
    getRegistry().getRule(name).run();
}


} // tools
} // maker
