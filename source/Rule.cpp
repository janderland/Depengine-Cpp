#include "Registry.hpp"
#include "Rule.hpp"
#include "Var.hpp"


Rule::Rule(RuleDetails&& details, const Registry& registry):
    _details(details), _registry(registry) { }


void Rule::runDependencies() const {
    for (REF dependency : _details.getDependencies()) {
        _registry.getRule(dependency).run();
    }
}


void Rule::run() const {
    runDependencies();
    if (_details.mustExecute()) {
        _details.execute();
    }
}
