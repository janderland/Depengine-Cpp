#include <iostream>

#include "DepException.hpp"
#include "Rule.hpp"


namespace depengine
{


void Rule::runDependencies() const
{
    for (const auto& dependency : _details._dependencies) {
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
        const auto result = _details.execute();
        if (!result.empty()) {
            _setter(result);
        }
    }
}


} // namespace depengine
