#pragma once

#include <string>

class Registry;
class Rule;


class Dependency {
private:
    const Registry& _registry;
    const std::string _product;

public:
    Dependency(const Registry& registry,
            const std::string& product);

    const std::string& product() const;
    const Rule& get() const;
};
