//
// Created by qwert on 24.10.2024.
//

#ifndef BOR_H
#define BOR_H

#endif //BOR_H

#include <string>
#include <map>

class BOR {
public:
    struct BorTree {
        bool terminal = false;
        std::map<char, BorTree*> childrens;
    };
    void Add(std::string a);
private:
    BorTree* head;
};