#pragma once

#include <string>
#include <vector>

#include "RuleDetails.hpp"
class Registry;


class Rule {
private:
    RuleDetails _details;
    const Registry& _registry;
    void runDependencies() const;

public:
    Rule(RuleDetails&& details, const Registry& registry);
    void run() const;
};
