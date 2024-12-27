#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>
#include <memory>
#include <stdexcept>


class Scope {
    public:
    Scope() = default;
    ~Scope() = default;
    void declare (std::string id, std::string type) { ids[id] = type; }
    bool isDeclared(std::string id) {
        return ids.empty() ? false : ids.find(id) != ids.end();
    }
    std::unordered_map<std::string, std::string> getIds() { return ids; }
    private:
    std::unordered_map<std::string, std::string> ids; // id and type
};

class TID {
    public:
    TID() { enterScope(); }
    ~TID() {}
    void enterScope() { scopes.push_back(std::make_unique<Scope>()); }
    std::unordered_map<std::string, std::string> getCurrentScope() { return scopes.back().get()->getIds(); }
    void exitScope() {
        if (scopes.empty()) {
            throw std::runtime_error("No scope to exit");
        }
        scopes.pop_back();
    }

    void declare(const std::string& id, const std::string& type = "") {
        scopes.back()->declare(id, type);
    }

    bool isDeclared(const std::string& name) {
        bool ans = false;
        for (auto it = scopes.begin(); it != scopes.end(); ++it) {
            if ((*it)->isDeclared(name)) {
                ans = true;
            }
        }
        return ans;
    }

    private:
    std::vector<std::unique_ptr<Scope>> scopes;
};

struct expr {
    std::string type;
    std::vector <std::string> args;
};