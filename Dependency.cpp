#include "Dependency.hpp"
#include "Registry.hpp"


Dependency::Dependency(
        const Registry& registry,
        const std::string& product):
    _registry(registry),
    _product(product) { }


const std::string& Dependency::product() const {
    return _product;
}

        
const Rule& Dependency::get() const {
    return _registry.get(_product);
}
