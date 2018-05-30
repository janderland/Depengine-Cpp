#include <iostream>
#include <sstream>

#include "DepException.hpp"
#include "RuleDetails.hpp"
#include "FileInfo.hpp"
#include "Var.hpp"


namespace depengine {
using std::stringstream;
using std::cout;
using std::endl;


RuleDetails::RuleDetails(
        const string& product,
        const vector<string>& dependencies,
        const Action& action):
    _product(product),
    _dependencies(dependencies),
    _action(action) { }


const string& RuleDetails::getProduct() const {
    return _product;
}


const vector<string>&
        RuleDetails::getDependencies() const {
    return _dependencies;
}


const Action& RuleDetails::getAction() const {
    return _action;
}


bool RuleDetails::mustExecute() const {
    cout << "Checking state of \"" << _product
        << "\"..." << endl;

    VAL prodFile = FileInfo::get(_product);
    if (prodFile.exists)
    {
        cout << "\"" << _product << "\" exists." << endl;
        for (REF dependency : _dependencies) {
            VAL depFile = FileInfo::get(dependency);
            if (depFile.exists) {
                if (depFile.lastChange > prodFile.lastChange) {
                    cout << "Dependency \"" << dependency
                        << "\" is newer than \""
                        << _product << "\"."
                        << endl;
                    return true;
                }
            }
            else {
                stringstream message;
                message << "Dependency \"" << dependency
                    << "\" doesn't exist." << endl;
                // throw DepException(message.str());
                cout << message.str();
            }
        }
        return false;
    }
    else {
        cout << "\"" << _product << "\" doesn't exist." << endl;
        return true;
    }
}


void RuleDetails::execute() const {
    _action(_product, _dependencies);
}


} // namespace depengine
