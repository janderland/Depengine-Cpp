#include <iostream>
#include <utility>
#include "Registry.hpp"
#include "Rule.hpp"


void Registry::run(const std::string& product) const {
    if (rules.find(product) == rules.end()) {
        std::cerr << "No rule found for \"" << product
            << "\"." << std::endl;
    }
    else {
        const Rule& rule = rules.at(product);
        if (!rule.productExists()) {
            rule.runDependencies(this);
            rule.executeRule();
        }
    }
}
