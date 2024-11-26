#pragma once
#include <string>
#include <vector>
#include "Bor.h"

enum Type {
    KEYWORD, // base
    IDENTIFIER, // base
    INTEGER, // int
    FLOAT, // float
    STRING, // string with ""
    CHARACTER, // char with ''
    TYPE, // kwords double, int ect.
    BOOLEAN, // true or false kwords
    OPERATOR, // operation kwords
    NONE, // empty
    COMMA, // ,
    LEFTBRASKET, // (
    RIGHTBRASKET, // )    
    LEFTFIGUREBRASKET, // {
    RIGHTFIGUREBRASKET, // }
    LEFTSQUAREBRASKET, // [
    RIGHTSQUAREBRASKET, // ]
    COLON, // :
    DOTXCOMMA // ;
};

const std::string NASTRING = "~~~~~~";

struct Lexeme
{
    Lexeme() = default;
    ~Lexeme() = default;
    std::string value_ = "~~~~~~";
    Type type_ = Type::NONE;
    BOR Bor;
    int line_number_ = 0;
    int column_number_ = 0;
    int i = 0;
};

bool isType(Lexeme lex);
bool isLetter(char c);
bool isOp(char word);
std::string Slise(std::string a, int b, int c);
std::vector<Lexeme> AnalyzeLexeme();