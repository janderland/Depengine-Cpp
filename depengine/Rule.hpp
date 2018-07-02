#pragma once

#include "RuleDetails.hpp"


namespace depengine
{
using namespace boost;
using namespace std;

class Registry;


class Rule
{
private:
    Registry& _registry;
    function<void(any)> _setter;
    const RuleDetails _details;

    void runDependencies() const;

public:
    Rule(
        Registry& registry,
        function<void(any)>& setter,
        const RuleDetails& details
    );

    void run() const;
};


} // namespace depengine
