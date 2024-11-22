#include "parser.h"

void Parser::match(Type other) {
    if (lexemes[pos].type_ == other) {
        ++pos;
        return;
    }
    else {
        throw std::runtime_error("SYNTAX ERROR\nUnexpected token in line " + std::to_string(lexemes[pos].line_number_ + 1) + ": " + lexemes[pos].value_ + "\n Expected: " + std::to_string(other) + ", but got: " + std::to_string(lexemes[pos].type_));
    }
}

void Parser::declaration() {
    if (pos >= lexemes.size()) {
        return;
    }
    if (lexemes[pos].type_ == Type::TYPE) {
        if (lexemes[pos + 1].type_ == Type::IDENTIFIER && lexemes[pos + 2].type_ == Type::LEFTBRASKET) {
            function();
            declaration();
        }
        else if (lexemes[pos + 2].type_ == Type::OPERATOR && lexemes[pos + 2].value_ == "=") {
            variable();
            declaration(); // global variables
        } 
    } else {
        match(Type::TYPE);
    }
}

void Parser::function() {
    match(Type::TYPE);
    match(Type::IDENTIFIER);
    match(Type::LEFTBRASKET);
    parameters();
    match(Type::RIGHTBRASKET);
    block();
}

void Parser::variable() {
    match(Type::TYPE);
    match(Type::IDENTIFIER);
    if (lexemes[pos].value_ == "=") {
        match(Type::OPERATOR);
        expression();
        match(Type::DOTXCOMMA);
    }
    else if (lexemes[pos].value_ == ",") {
        match(Type::COMMA);
        variable();
    }
    else if (lexemes[pos].value_ == ";") {
        match(Type::DOTXCOMMA);
    }
    else {
        throw std::runtime_error("SYNTAX ERROR\nUnexpected token in line " + std::to_string(lexemes[pos].line_number_ + 1) + "\nExpected definiton of variable");
    }
}

void Parser::parameters() {
    while (lexemes[pos].type_ == Type::TYPE) {
        parameter();
    }
}

void Parser::parameter() {
    match(Type::TYPE);
    match(Type::IDENTIFIER);
}

void Parser::block() {
    match(Type::LEFTFIGUREBRASKET);
    instruction();
    match(Type::RIGHTFIGUREBRASKET);
}


void Parser::instruction() {
    if (lexemes[pos].value_ == "if") {
        ifinstruct();
        instruction();
    }
    else if (lexemes[pos].value_ == "switch") {
        cases();
        instruction();
    }
    else if (lexemes[pos].value_ == "while") {
        cycle();
        instruction();
    }
    else if (lexemes[pos].value_ == "for") {
        cycle();
        instruction();
    }
    if (lexemes[pos].value_ == "return") {
        match(Type::IDENTIFIER);
        expression();
        match(Type::DOTXCOMMA);
        instruction();
    }
    if (lexemes[pos].value_ == "break" || lexemes[pos].value_ == "continue") {
        match(Type::IDENTIFIER);
        match(Type::DOTXCOMMA);
        instruction();
    }
    if (lexemes[pos].type_ == Type::TYPE) {
        ooperator();
        instruction();
    }
}


void Parser::ooperator() {
    if (lexemes[pos].type_ == Type::TYPE) {
        match(Type::TYPE);
        if (lexemes[pos + 1].type_ == Type::OPERATOR) {
            match(Type::IDENTIFIER);
            match(Type::OPERATOR);
            expression();
            match(Type::DOTXCOMMA);
        } else {
            match(Type::DOTXCOMMA);
        }
    }
}

void Parser::cycle() {
    if (lexemes[pos].type_ == Type::IDENTIFIER) {
        if (lexemes[pos].value_ == "while") {
            match(Type::IDENTIFIER);
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
            block();
        } else if (lexemes[pos].value_ == "for") {
            match(Type::IDENTIFIER);
            match(Type::LEFTBRASKET);
            initialization();
            // match(Type::DOTXCOMMA);
            expression();
            match(Type::DOTXCOMMA);
            step();
            match(Type::RIGHTBRASKET);
            block();
        }
    }
}

void Parser::initialization() {
    ooperator();
}

void Parser::step() {
    expression();
}

void Parser::ifinstruct() {
    if (lexemes[pos].type_ == Type::IDENTIFIER) {
        if (lexemes[pos].value_ == "if") {
            match(Type::IDENTIFIER);
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
            block();
            if (lexemes[pos].type_ == Type::IDENTIFIER) {
                if (lexemes[pos].value_ == "else") {
                    match(Type::IDENTIFIER);
                    block();
                }
            }
        } else if (lexemes[pos].value_ == "switch") {
            match(Type::IDENTIFIER);
            match(Type::LEFTBRASKET);
            match(Type::STRING);
            match(Type::RIGHTBRASKET);
            match(Type::LEFTFIGUREBRASKET);
            cases();
            match(Type::RIGHTFIGUREBRASKET);
        } 
    }
}

void Parser::cases() {
    if (lexemes[pos].type_ == Type::IDENTIFIER) {
        if (lexemes[pos].value_ == "case") {
            match(Type::IDENTIFIER);
            match(Type::STRING);
            match(Type::COLON);
            block();
            cases();
        }
    }
}

void Parser::expression() {
    expr0();
    while (lexemes[pos].type_ == Type::COMMA) {
        match(Type::COMMA);
        expression();
    }
    while (lexemes[pos].type_ == Type::OPERATOR) {
        if (lexemes[pos].value_ == "<" || lexemes[pos].value_ == ">" || lexemes[pos].value_ == ">=" || lexemes[pos].value_ == "<=" || lexemes[pos].value_ == "==" || lexemes[pos].value_ == "!=" || lexemes[pos].value_ == "=" ) {
            match(Type::OPERATOR);
            expression();
        }
    }
}

void Parser::expr0() {
    if (lexemes[pos].type_ == Type::OPERATOR && lexemes[pos].value_ == "!") {
        match(Type::OPERATOR);
    }
    expr1();
}

void Parser::expr1() {
    expr2();
    while (lexemes[pos].type_ == Type::OPERATOR && lexemes[pos].value_ == "||") {
        match(Type::OPERATOR);
        expr2();
    }
}

void Parser::expr2() {
    expr3();
    while (lexemes[pos].type_ == Type::OPERATOR && lexemes[pos].value_ == "&&") {
        match(Type::OPERATOR);
        expr3();
    }
}

void Parser::expr3() {
    expr4();
    while (lexemes[pos].type_ == Type::OPERATOR && (lexemes[pos].value_ == "+" || lexemes[pos].value_ == "-")) {
        match(Type::OPERATOR);
        expr4();
    }
}

void Parser::expr4() {
    expr5();
    while (lexemes[pos].type_ == Type::OPERATOR && (lexemes[pos].value_ == "*" || lexemes[pos].value_ == "/" || lexemes[pos].value_ == "%")) {
        match(Type::OPERATOR);
        expr5();
    }
}

void Parser::expr5() {
    expr6();
    while (lexemes[pos].type_ == Type::OPERATOR && lexemes[pos].value_ == "**") {
        match(Type::OPERATOR);
        expr6();
    }
}

void Parser::expr6() {
    if (lexemes[pos].type_ == Type::STRING) {
        if (lexemes[pos].value_ != std::to_string('"')) {
            throw std::invalid_argument("SYNTAX ERROR\nInvalid expression in line " + std::to_string(lexemes[pos].line_number_ + 1));
        }
        match(Type::STRING);
        if (lexemes[pos].value_ != std::to_string('"')) {
            throw std::invalid_argument("SYNTAX ERROR\nInvalid expression in line " + std::to_string(lexemes[pos].line_number_ + 1));
        }
    } else if (lexemes[pos].type_ == Type::INTEGER) {
        match(Type::INTEGER);
    } else if (lexemes[pos].type_ == Type::IDENTIFIER) {
        match(Type::IDENTIFIER);
    } else if (lexemes[pos].type_ == Type::BOOLEAN) {
        match(Type::BOOLEAN);
    } else if (lexemes[pos].type_ == Type::LEFTBRASKET) {
        match(Type::LEFTBRASKET);
        expression();
        match(Type::RIGHTBRASKET);
    } else {
        throw std::invalid_argument("SYNTAX ERROR\nInvalid expression in line " + std::to_string(lexemes[pos].line_number_ + 1));
    }
}