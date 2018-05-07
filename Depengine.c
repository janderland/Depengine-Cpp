#include <stdio.h>
#include <string.h>


struct Dependency {
    char* product;
    struct Dependency* next;
};


struct Rule {
    char* product;
    char* command;
    struct Dependency* dependencies;
};


struct Registry {
    struct Rule* rule;
    struct Registry* next;
};


int productExists(const char*);
struct Rule* findRule(struct Registry*, const char*);
int runDependencies(struct Registry*, struct Dependency*);
int executeRule(struct Rule*);
int run(struct Registry*, struct Rule*);


int productExists(const char* product) {
    printf("Checking if \"%s\" exists...\n", product);
    FILE* file = fopen(product, "r");
    if (file)
    {
        printf("Product exists.\n");
        fclose(file);
        return 1;
    }
    printf("Product doesn't exist.\n");
    return 0;
}


struct Rule* findRule(struct Registry* registry, const char* product) {
    printf("Searching for rule for \"%s\"...\n", product);
    while (registry) {
        if (strcmp(registry->rule->product, product) == 0) {
            printf("Rule found.\n");
            return registry->rule;
        }
        registry = registry->next;
    }
    printf("Rule not found.\n");
    return NULL;
}


int runDependencies(struct Registry* registry, struct Dependency* dependency) {
    struct Rule* rule;
    while (dependency) {
        rule = findRule(registry, dependency->product);
        if (rule == NULL) {
            return 0;
        }
        run(registry, rule);
        dependency = dependency->next;
    }
    return 1;
}


int executeRule(struct Rule* rule) {
    printf("Executing command \"%s\"...\n", rule->command);
    FILE* pipe = popen("bash", "w");
    if (pipe) {
        fprintf(pipe, "%s\n", rule->command);
        if (pclose(pipe) != 0) {
            printf("Command failed on exit.\n");
            return 0;
        }
        return 1;
    }
    printf("Command failed on start.\n");
    return 0;
}


int run(struct Registry* registry, struct Rule* rule) {
    if (productExists(rule->product)) {
        return 1;
    }

    if (runDependencies(registry, rule->dependencies) != 1) {
        return 0;
    }

    if (executeRule(rule) != 1) {
        return 0;
    }

    return 1;
}


int main() {
    struct Rule rule2 = { "file2", "touch file2", NULL };
    struct Rule rule1 = { "file1", "touch file1", NULL };

    struct Registry registry2 = { &rule2, NULL };
    struct Registry registry1 = { &rule1, &registry2 };

    struct Dependency dep2 = { "file2", NULL };
    struct Dependency dep1 = { "file1", &dep2 };
    struct Rule root = { "root", "touch root", &dep1 };

    run(&registry1, &root);
}
