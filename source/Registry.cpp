#include <iostream>
#include <utility>
#include <sstream>

#include "DepException.hpp"
#include "Registry.hpp"


const Rule& Registry::get(const std::string& product) const {
    const auto& location = rules.find(product);
    if (location == rules.end()) {
        std::stringstream message;
        message << "No rule found for \""
            << product << "\".";
        throw DepException(message.str());
    }
    else return location->second;
}
