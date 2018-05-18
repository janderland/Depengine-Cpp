#pragma once

#include <string>

class Rule;
class Registry;


class Dependency {
private:
    const Registry& _registry;
    const std::string _product;

public:
    Dependency(const Registry& registry,
            const std::string& product);

    const Rule& get() const;
};
