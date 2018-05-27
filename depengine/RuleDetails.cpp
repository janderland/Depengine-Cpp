#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "DepException.hpp"
#include "RuleDetails.hpp"
#include "FileInfo.hpp"
#include "Var.hpp"


namespace depengine {
using std::stringstream;
using std::cout;
using std::endl;


RuleDetails::RuleDetails(
        string product,
        vector<string> dependencies,
        function<void()> action):
    _product(move(product)),
    _dependencies(move(dependencies)),
    _action(move(action)) { }


const string& RuleDetails::getProduct() const {
    return _product;
}


const vector<string>&
        RuleDetails::getDependencies() const {
    return _dependencies;
}


bool RuleDetails::mustExecute() const {
    cout << "Checking \"" << _product
        << "\"." << endl;

    VAL prodFile = FileInfo::get(_product);
    if (prodFile.exists)
    {
        cout << "Product exists." << endl;
        for (REF dependency : _dependencies) {
            VAL depFile = FileInfo::get(dependency);
            if (depFile.exists) {
                if (depFile.lastChange > prodFile.lastChange) {
                    cout << "Dependency \"" << dependency
                        << "\" is newer than product."
                        << endl;
                    return true;
                }
            }
            else {
                stringstream message;
                message << "Dependency \"" << dependency
                    << "\" doesn't exist." << endl;
                throw DepException(message.str());
            }
        }
        return false;
    }
    else {
        cout << "Product doesn't exist." << endl;
        return true;
    }
}


void RuleDetails::execute() const {
    _action();
}


} // namespace depengine
