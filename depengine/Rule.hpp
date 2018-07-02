#pragma once

#include "RuleDetails.hpp"


namespace depengine
{
using namespace boost;
using namespace std;


class Rule
{
private:
    void runDependencies() const;

public:
    const function<const Rule&(string)> _getter;
    const function<void(any)> _setter;
    const RuleDetails _details;

    void run() const;
};


} // namespace depengine
