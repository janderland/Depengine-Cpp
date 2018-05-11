#pragma once

#include <vector>
#include <string>
#include <map>
#include "Rule.hpp"


class Registry {
public:
    std::map<std::string, Rule> rules;

    void run(const std::string& product) const;

    template <class ...Strings>
    void createRule(const std::string& product,
            const std::string& command,
            Strings... dependencies) {
        std::vector<std::string> deplist = {
            dependencies...
        };
        rules.emplace(std::make_pair(product,
            Rule(product, command, std::move(deplist))));
    }
};
