#include <iostream>

#include "DepException.hpp"
#include "Registry.hpp"
#include "Rule.hpp"
#include "Var.hpp"


namespace depengine {
using std::cerr;
using std::endl;


Rule::Rule(RuleDetails&& details, const Registry& registry):
    _details(details), _registry(registry) { }


void Rule::runDependencies() const {
    for (REF dependency : _details.getDependencies()) {
        try { _registry.getRule(dependency).run(); }
        catch (const DepException& err) {
            cerr << "Warning: "
                << err.what()
                << endl;
        }
    }
}


void Rule::run() const {
    runDependencies();
    if (_details.mustExecute()) {
        _details.execute();
    }
}


} // namespace depengine
