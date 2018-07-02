#pragma once

#include "RuleDetails.hpp"


namespace depengine
{
using namespace boost;
using namespace std;


class Rule
{
private:
    function<const Rule&(string)> _getter;
    function<void(any)> _setter;
    const RuleDetails _details;

    void runDependencies() const;

public:
    Rule(
        const function<const Rule&(string)>& getter,
        const function<void(any)>& setter,
        const RuleDetails& details
    );

    void run() const;
};


} // namespace depengine
