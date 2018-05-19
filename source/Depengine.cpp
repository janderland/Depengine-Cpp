#include "Registry.hpp"
#include "Rule.hpp"


int main() {
    Registry registry;
    registry.createRule("file1", "touch file1");
    registry.createRule("file2", "touch file2");
    registry.createRule("root", "touch root", "file1", "file2");
    registry.get("root").run();
}
