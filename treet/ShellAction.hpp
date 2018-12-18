#pragma once

#include <boost/any.hpp>
#include <string>
#include <vector>

#include "depengine/Registry.hpp"


namespace treet {
using namespace depengine;
using namespace boost;
using namespace std;


class ShellAction {
private:
  const vector<string> _commands;

public:
  ShellAction(const vector<string>& commands);

  any operator()(
    const string& product,
    const vector<string>& dependencies
  ) const;
};


} // namespace treet
