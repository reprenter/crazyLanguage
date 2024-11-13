#include "parser.h"

int pos = 0;

void Parser::match(Type other) {
    if (lexemes[pos].type_ == other) {
        pos += 1;
    }
    else {
        throw std::runtime_error("Unexpected token: " + lexemes[pos].value_);
    }
}

void Parser::declaration() {
    if (lexemes[pos].type_ == Type::TYPE) {
        if (lexemes[pos + 1].type_ == Type::IDENTIFIER && lexemes[pos + 2].type_ == Type::LEFTBRASKET) {
            function();
            declaration();
        }
        else if (lexemes[pos + 2].type_ == Type::OPERATOR && lexemes[pos + 2].value_ == "=") {
            variable();
            declaration();
        }
    }
}

void Parser::function() {
    match(Type::TYPE);
    match(Type::IDENTIFIER);
    if (lexemes[pos].type_ == Type::LEFTBRASKET) {
        match(Type::LEFTBRASKET);
        //parameters();
        match(Type::RIGHTBRASKET);
        if (lexemes[pos].type_ == Type::RIGHTBRASKET) {
            match(Type::LEFTFIGUREBRASKET);
            //statement();
            match(Type::RIGHTFIGUREBRASKET);
        }
    }
}

void Parser::variable() {
    match(Type::TYPE);
    match(Type::IDENTIFIER);
    if (lexemes[pos].value_ == "=") {
        match(Type::OPERATOR);
        //expression();
    }
    else if (lexemes[pos].value_ == ",") {
        match(Type::COMMA);
        variable();
    }
    else if (lexemes[pos].value_ == ";") {
        match(Type::DOTXCOMMA);
    }
    else {
        throw std::runtime_error("Syntax error");
    }
}