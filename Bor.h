#pragma once
//
// Created by qwert on 24.10.2024.
//

#ifndef BOR_H
#define BOR_H

#endif //BOR_H

#include <string>
#include <map>
#include <fstream>

class BOR {
public:
    struct BorTree {
        bool terminal = false;
        std::map<char, BorTree*> childrens;
    };
    BOR() { head == nullptr; }
    BOR(int a) {
        head = new BorTree;
        std::fstream cmds("keywords.txt");
        Read(cmds);
    }
    void Add(std::string a) {
        auto tree = head;
        for (auto i : a) {
            if(tree->childrens[i] == nullptr)tree->childrens[i] = new BorTree;
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