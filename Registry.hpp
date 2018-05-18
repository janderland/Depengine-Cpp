#pragma once

#include <vector>
#include <string>
#include <map>

#include "Dependency.hpp"
#include "Rule.hpp"


class Registry {
private:
    std::map<std::string, Rule> rules;

public:
    const Rule& get(const std::string& product) const;

    template <class ...Strings>
    void createRule(const std::string& product,
            const std::string& command,
            Strings... dependencies) {
        std::vector<std::string> prodlist = {
            dependencies...
        };
        std::vector<Dependency> deplist;
        for (const auto& product : prodlist) {
            deplist.emplace_back(*this, product);
        }
        rules.emplace(std::make_pair(std::string(product),
            Rule(product, command, std::move(deplist))));
    }
};
