#include <iostream>
#include <utility>
#include <sstream>

#include "DepException.hpp"
#include "Registry.hpp"
#include "Rule.hpp"
#include "Var.hpp"

using std::stringstream;
using std::make_pair;
using std::move;


const Rule& Registry::get(const string& product) const {
    REF location = rules.find(product);
    if (location == rules.end()) {
        stringstream message;
        message << "No rule found for \""
            << product << "\".";
        throw DepException(message.str());
    }
    else return location->second;
}


void Registry::createRule(RuleDetails&& details) {
    rules.emplace(make_pair(details.getProduct(),
        Rule(move(details), *this)));
}
