//
// Created by qwert on 24.10.2024.
//
#include "Bor.h"

void BOR::Add(std::string a) {
    auto tree = head;
    for (auto i : a) {
        tree = tree->childrens[i];
    }
    tree->terminal = true;
}