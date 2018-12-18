#include <iostream>
#include <sstream>

#include "RuleDetails.hpp"
#include "Registry.hpp"
#include "FileInfo.hpp"


namespace depengine {


bool RuleDetails::mustExecute() const {
  cout << "Checking state of \"" << _product << "\"..." << endl;

  const auto prodFile = FileInfo::get(_product);
  if (prodFile.exists) {
    cout << "\"" << _product << "\" exists on disk." << endl;
    for (const auto& dependency : _dependencies) {
      const auto depFile = FileInfo::get(dependency);
      if (depFile.exists) {
        if (depFile.lastChange > prodFile.lastChange) {
          cout << "Dependency \"" << dependency
             << "\" is newer than \"" << _product << "\"." << endl;
          return true;
        }
      }
      else {
        stringstream message;
        message << "Dependency \"" << dependency << "\" doesn't exist."
            << endl;
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


any RuleDetails::execute() const {
  return _action(_product, _dependencies);
}


} // namespace depengine
