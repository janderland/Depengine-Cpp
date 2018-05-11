#include <iostream>
#include <cstdio>
#include "Rule.hpp"
#include "Registry.hpp"


Rule::Rule(std::string product, std::string command,
        std::vector<std::string>&& dependencies):
    product(product),
    command(command),
    dependencies(dependencies) { }


bool Rule::productExists() const {
    std::cout << "Checking if \"" << this->product
        << "\" exists..." << std::endl;

    FILE* file = fopen(this->product.c_str(), "r");
    if (file)
    {
        std::cout << "Product exists." << std::endl;
        fclose(file);
        return true;
    }
    else {
        std::cout << "Product doesn't exist." << std::endl;
        return false;
    }
}


void Rule::runDependencies(const Registry* registry) const {
    std::cout << "Running dependencies for \""
        << this->product << "\"." << std::endl;

    for (const auto& dependency : this->dependencies) {
        registry->run(dependency);
    }

    std::cout << "Finished dependencies for \""
        << this->product << "\"." << std::endl;
}


void Rule::executeRule() const {
    std::cout << "Executing command \"" << this->command
        << "\"..." << std::endl;

    FILE* pipe = popen("bash", "w");
    if (pipe) {
        fprintf(pipe, "%s\n", this->command.c_str());
        if (pclose(pipe) != 0) {
            std::cerr << "Command failed on exit."
                << std::endl;
        }
    }
    else {
        std::cerr << "Command failed on start."
            << std::endl;
    }
}
