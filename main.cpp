#include <iostream>
#include <vector>

#include "lexemeanalyzer.h"

std::string coutType(Type other) {
    switch (other)
    {
    case Type::BOOLEAN:
        return "Bool";
        break;
    case Type::CHARACTER:
        return "Char";
    case Type::FLOAT:
        return "Float";
    case Type::IDENTIFIER:
        return "ID";
    case Type::INTEGER:
        return "INT";
    case Type::KEYWORD:
        return "KEYWORD";
    case Type::NONE:
        return "NONE";
    case Type::OPERATOR:
        return "Operator";
    case Type::STRING:
        return "String";
    }
    return "";
}

int main() {
    std::vector<Lexeme> lexemes = AnalyzeLexeme();
    for (int i = 0; i < lexemes.size(); i++) {
        std::cout << lexemes[i].value_ << ' ' << coutType(lexemes[i].type_) << std::endl;

    }
    return 0;
}