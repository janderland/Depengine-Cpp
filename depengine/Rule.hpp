#pragma once

#include "RuleDetails.hpp"


namespace depengine {
class Registry;


class Rule {
private:
    Registry& _registry;
    const RuleDetails _details;
    void runDependencies() const;

public:
    Rule(Registry& registry, const RuleDetails& details);
    void run() const;
};


} // namespace depengine
