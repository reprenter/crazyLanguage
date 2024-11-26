#pragma once
#include <string>
#include <map>
#include <fstream>

class BOR {
public:
    struct BorTree {
        bool terminal = false;
        std::map<char, BorTree*> childrens;
    };
    BOR() { head = nullptr; }
    ~BOR() {}
    BOR(int a) {
        head = new BorTree;
        std::fstream cmds("keywords.txt");
        Read(cmds);
    }
    void Add(std::string a) {
        auto tree = head;
        for (auto i : a) {
            if (tree->childrens[i] == nullptr)tree->childrens[i] = new BorTree;
            tree = tree->childrens[i];
        }
        tree->terminal = true;
    }

    bool Find(std::string a) {
        auto tree = head;
        for (auto i : a) {
            if (tree->childrens[i] == nullptr) {
                return false;
            }
            else {
                tree = tree->childrens[i];
            }
        }
        if(tree == nullptr) return false;
        return tree->terminal;
    }
    void Read(std::fstream& f) {
        std::string line;
        while (getline(f, line)) {
            this->Add(line);
        }
    }
private:
    BorTree* head;
};