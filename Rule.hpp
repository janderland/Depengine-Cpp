#pragma once

#include <string>
#include <vector>

#include "Dependency.hpp"


class Rule {
private:
    const std::string _product;
    const std::string _command;
    const std::vector<Dependency> _dependencies;

public:
    Rule(const std::string& product, const std::string& command,
            std::vector<Dependency>&& dependencies);

    void run() const;
};
