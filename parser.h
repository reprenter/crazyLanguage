#pragma once
#include <vector>
#include "lexemeanalyzer.h"

class Parser {
public:
    Parser() { lexemes = AnalyzeLexeme(); };
    ~Parser() = default;
    void parse() { program(); };
private:
    void declaration();
    void program() { declaration(); };
    void match(Type other);
    void function();
    void variable();
    //void parameters();
    //void statement();
    //void expression();
    std::vector <Lexeme> lexemes;
};
