#pragma once

#include <string>
#include <vector>


class Registry;


class Rule {
public:
    const std::string product;
    const std::string command;
    const std::vector<std::string> dependencies;

    Rule(std::string product, std::string command,
            std::vector<std::string>&& dependencies);

    bool productExists() const;
    void runDependencies(const Registry* registry) const;
    void executeRule() const;
};
