#include <iostream>
#include <utility>
#include <sstream>

#include "DepException.hpp"
#include "Registry.hpp"
#include "Rule.hpp"


const Rule& Registry::get(const std::string& product) const {
    if (rules.find(product) == rules.end()) {
        std::stringstream message;
        message << "No rule found for \""
            << product << "\".";
        throw DepException(message.str());
    }
    else return rules.at(product);
}
