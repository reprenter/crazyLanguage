#include <iostream>
#include <vector>
#include <sstream>

#include "parser.h"
#include "toPolish.h"

int main() {
    std::vector<Lexeme> lexemes = AnalyzeLexeme();
    Parser parser(lexemes);
    try {
        parser.parse(); 
        std::cout << "Syntax analysis passed." << '\n';
        std::cout << "Semantics analysis passed." << '\n';
    } catch (std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }
    std::vector<Lexeme> Polish = toPolishNotation(lexemes);
    for (auto i : Polish) {
        std::cout << i.value_ << ' ';
    }
    return 0;
}