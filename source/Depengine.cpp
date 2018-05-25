#include "RuleDetails.hpp"
#include "Registry.hpp"
#include "Rule.hpp"


int main() {
    Registry registry;
    registry.createRule(RuleDetails("file1", "touch file1"));
    registry.createRule(RuleDetails("file2", "touch file2"));
    registry.createRule(RuleDetails("root", "touch root", { "file1", "file2" }));
    registry.getRule("root").run();
}
