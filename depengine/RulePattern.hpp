#pragma once

#include <string>
#include <vector>
#include <regex>

#include "RuleDetails.hpp"
#include "Rule.hpp"
#include "Var.hpp"


namespace depengine {
using std::string;
using std::vector;
using std::regex;
class Registry;


class RulePattern {
private:
    Registry& _registry;
    const regex _prodPattern;
    const vector<string> _depPatterns;
    const Action _action;

    vector<string> getDependencies(
            const string& product) const;

public:
    RulePattern(
            Registry& registry,
            const RuleDetails& details);

    bool matches(const string& product) const;
    Rule getRule(const string& product) const;
};


} // namespace depengine
