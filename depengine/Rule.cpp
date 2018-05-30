#include <iostream>

#include "DepException.hpp"
#include "Registry.hpp"
#include "Rule.hpp"
#include "Var.hpp"


namespace depengine {
using std::cout;
using std::endl;


Rule::Rule(Registry& registry, const RuleDetails& details):
    _registry(registry), _details(details)  { }


void Rule::runDependencies() const {
    for (REF dependency : _details.getDependencies()) {
        const Rule* rule = nullptr;
        try { rule = &_registry.getRule(dependency); }
        catch (const DepException& err) {
            cout << err.what()
                 << endl;
        }
        if (rule) rule->run();
    }
}


void Rule::run() const {
    runDependencies();
    if (_details.mustExecute()) {
        _details.execute();
    }
}


} // namespace depengine
