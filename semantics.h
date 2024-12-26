#pragma once
#include "parser.h"
#include <unordered_map>
#include <stack>
#include <memory>

class Scope {
    public:
    void declare (std::string id) {
        ids[id] = true;
    }
    bool isDeclared(std::string id) {
        return ids.find(id) != ids.end();
    }
    private:
    std::unordered_map<std::string, bool> ids;
};

class TID {
    public:
    void enterScope() {
        scopes.push_back(std::make_unique<Scope>());
    }
    
    void exitScope() {
        if (scopes.empty()) {
            throw std::runtime_error("No scope to exit");
        }
        scopes.pop_back();
    }

    void declare(const std::string& id) {
        scopes.back()->declare(id);
    }

    bool isDeclared(const std::string& name) {
        for (auto it = scopes.begin(); it != scopes.end(); ++it) {
            if ((*it)->isDeclared(name)) {
                return true;
            }
        }
        return false;
    }

    private:
    std::vector<std::unique_ptr<Scope>> scopes;
};