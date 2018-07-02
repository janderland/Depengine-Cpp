#include <iostream>

#include "DepException.hpp"
#include "Rule.hpp"
#include "Var.hpp"


namespace depengine
{


void Rule::runDependencies() const
{
    for (REF dependency : _details.getDependencies()) {
        const Rule* rule = nullptr;
        try {
            rule = &_getter(dependency);
        }
        catch (const DepException& err) {
            cout << err.what() << endl;
        }
        if (rule) {
            rule->run();
        }
    }
}


void Rule::run() const
{
    runDependencies();
    if (_details.mustExecute()) {
        VAL result = _details.execute();
        if (!result.empty()) {
            _setter(result);
        }
    }
}


} // namespace depengine
