#pragma once
#include <vector>
#include "lexemeanalyzer.h"
#include <iostream>
#include "semantics.h"

class Parser {
public:
    Parser() { 
        lexemes = AnalyzeLexeme();
    };
    std::vector<Lexeme> Lexemes(){
        return lexemes;
    }
    ~Parser() = default;
    void parse() { program(); };
private:
    void saveFromSegFault();
    void declaration();
    void program() { declaration(); };
    void match(Type other);
    void function();
    void variable();
    void parameters();
    void parameter();
    void block();
    void instruction();
    void ifinstruct();
    void cases();
    void expression();
    void expr0();
    void expr1();
    void expr2();
    void expr3();
    void expr4();
    void expr5();
    void expr6();
    void initialization();
    void step();
    void ooperator();
    void cycle();
    std::vector <Lexeme> lexemes;
    int pos = 0;
};