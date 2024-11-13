#pragma once
#include <string>
#include "Bor.h"

enum Type {
    KEYWORD, // +
    TYPE,
    IDENTIFIER, // +
    INTEGER, //+
    STRING, // +
    FLOAT, //+
    CHARACTER, // +
    BOOLEAN, // +
    OPERATOR, // +
    NONE,
    COMMA, //,
    LEFTBRASKET, //(
    RIGHTBRASKET, //)
    LEFTFIGUREBRASKET, // {
    RIGHTFIGUREBRASKET, // }
    LEFTSQUAREBRASKET, //[
    RIGHTSQUAREBRASKET, //]
    COLON, //:
    DOTXCOMMA //;
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

#include <vector>

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') or (c >= 'A' && c <= 'Z') or c == '_';
}
bool isOp(char word) {
    std::string Word;
    Word += word;
    for (auto i : { "=", "==", "<", "<=", ">", ">=", "!", "&", "&&", "|", "||", "/", "/=", "*", "*=", "-", "-=", "+", "+=" }) {
        if (Word == i) return true;
    }
    return false;
}
std::string Slise(std::string a, int b, int c) {
    std::string ans = "";
    for (int i = b; i < c; i++) {
        ans += a[i];
    }
    return ans;
}
std::vector<Lexeme> AnalyzeLexeme() {
    std::vector<Lexeme> ans;
    std::string lexeme;
    Lexeme lex;
    int pos = 0;
    BOR Bor(1);
    std::ifstream ifs("code.txt");
    std::string code = "", temp;


    while (!ifs.eof()) {
        getline(ifs, temp);
        lexeme += temp + '\n';
    }
    Type oldLex = Type::NONE;
    for (int i = 0, j = 0; i < lexeme.size(); i++, j++) {
        if ((oldLex == Type::STRING and lexeme[i] != '"') or (oldLex == Type::CHARACTER and lexeme[i] != '\'')) {
            if (lexeme[i] != '\n') continue;
        }
        if (isLetter(lexeme[i])) {
            if (oldLex == Type::IDENTIFIER) {
                continue;
            }
            else {
                oldLex = Type::IDENTIFIER;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::IDENTIFIER;
                lex.Bor = Bor;
                if (ans.size() != 0) {
                    if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                }
                ans.push_back(lex);
            }
        }
        if (isOp(lexeme[i])) {
            if (oldLex == Type::STRING) continue;
            if (oldLex == Type::CHARACTER) continue;
            if (oldLex == Type::OPERATOR) {
                oldLex = Type::NONE;
            }
            else {
                oldLex = Type::OPERATOR;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::OPERATOR;
                lex.Bor = Bor;
                if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                ans.push_back(lex);
            }
        }
        if (lexeme[i] >= '0' and lexeme[i] <= '9') {
            if (oldLex == Type::INTEGER or oldLex == Type::FLOAT or oldLex == Type::KEYWORD or oldLex == Type::IDENTIFIER) {
                continue;
            }
            else {
                oldLex = Type::INTEGER;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::INTEGER;
                lex.Bor = Bor;
                if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                ans.push_back(lex);
            }
        }
        if (lexeme[i] == '.') {
            if (oldLex == Type::INTEGER or oldLex == Type::FLOAT) {
                oldLex = Type::FLOAT;
                ans[ans.size() - 1].type_ = Type::FLOAT;
            }
            else {
                oldLex = Type::FLOAT;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::FLOAT;
                lex.Bor = Bor;
                if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                ans.push_back(lex);
            }
        }
        if (lexeme[i] == '"') {
            if (oldLex == Type::STRING) {
                oldLex = Type::NONE;
            }
            else {
                oldLex = Type::STRING;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::STRING;
                lex.Bor = Bor;
                if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                ans.push_back(lex);
            }
        }
        if (lexeme[i] == '\'') {
            if (oldLex == Type::CHARACTER) {
                oldLex = Type::NONE;
            }
            else {
                oldLex = Type::CHARACTER;
                lex.column_number_ = j;
                lex.i = i;
                lex.line_number_ = pos;
                lex.type_ = Type::CHARACTER;
                lex.Bor = Bor;
                if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
                ans.push_back(lex);
            }
        }
        if (lexeme[i] == ' ' or lexeme[i] == '\n' or lexeme[i] == '\t') {
            oldLex = Type::NONE;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::NONE;
            lex.Bor = Bor;
            if (ans.size() != 0)if(ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
        }
        if (lexeme[i] == '\n') {
            j = 0;
        }
        switch (lexeme[i]) {
        case ',':
            oldLex = Type::COMMA;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::COMMA;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case '(':
            oldLex = Type::LEFTBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::LEFTBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case')':

            oldLex = Type::RIGHTBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::RIGHTBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case '{':
            oldLex = Type::LEFTFIGUREBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::LEFTFIGUREBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case'}':

            oldLex = Type::RIGHTFIGUREBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::RIGHTFIGUREBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case'[':

            oldLex = Type::LEFTSQUAREBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::LEFTSQUAREBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case']':

            oldLex = Type::RIGHTSQUAREBRASKET;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::RIGHTSQUAREBRASKET;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case':':
            oldLex = Type::COLON;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::COLON;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        case';':
            oldLex = Type::DOTXCOMMA;
            lex.column_number_ = j;
            lex.i = i;
            lex.line_number_ = pos;
            lex.type_ = Type::DOTXCOMMA;
            lex.Bor = Bor;
            if (ans.size() != 0)if (ans[ans.size() - 1].value_ == NASTRING) ans[ans.size() - 1].value_ = Slise(lexeme, ans[ans.size() - 1].i, i);
            ans.push_back(lex);
            break;
        }
        if (Bor.Find(ans[ans.size() - 1].value_) and ans[ans.size() - 1].type_ == Type::IDENTIFIER)
            ans[ans.size() - 1].type_ = Type::KEYWORD;

        //�������� ����������: ,:;(){}[]
    }
    return ans;
}
/*COMMA, //,
    LEFTBRASKET, //(
    RIGHTBRASKET, //)
    LEFTFIGUREBRASKET, // {
    RIGHTFIGUREBRASKET, // }
    LEFTSQUAREBRASKET, //[
    RIGHTSQUAREBRASKET, //]
    COLON, //:
    DOTXCOMMA //;*/