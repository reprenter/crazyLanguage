#include "parser.h"

std::string convertTypeToString(Type type) {
    switch (type) {
    case Type::NONE:
        return "NONE";
    case Type::TYPE:
        return "TYPE";
    case Type::IDENTIFIER:
        return "IDENTIFIER";
    case Type::STRING:
        return "STRING LITERAL";
    case Type::INTEGER:
        return "INTEGER";
    case Type::BOOLEAN:
        return "BOOLEAN";
    case Type::LEFTBRASKET:
        return "LEFT BRASKET";
    case Type::RIGHTBRASKET:
        return "RIGHT BRASKET";
    case Type::OPERATOR:
        return "OPERATOR";
    case Type::COMMA:
        return "COMMA";
    case Type::DOTXCOMMA:
        return "DOTXCOMMA";
    case Type::LEFTFIGUREBRASKET:
        return "LEFT FIGURE BRASKET";
    case Type::RIGHTFIGUREBRASKET:
        return "RIGHT FIGURE BRASKET";
    case Type::LEFTSQUAREBRASKET:
        return "LEFT SQUARE BRASKET";
    case Type::RIGHTSQUAREBRASKET:
        return "RIGHT SQUARE BRASKET";
    case Type::COLON:
        return "COLON";
    case Type::KEYWORD:
        return "KEYWORD";
    default:
        return "UNKNOWN";
    }
}

void Parser::saveFromSegFault() {
    Lexeme lex1, lex2;
    lex1.type_ = Type::NONE;
    lex1.value_ = "";
    lex1.line_number_ = 0;
    lexemes.push_back(lex1);
    lex2.type_ = Type::NONE;
    lex2.value_ = "";
    lex2.line_number_ = 0;
    lexemes.push_back(lex2);
}

void Parser::match(Type other) {
    if (lexemes[pos].type_ == other) {
        ++pos;
        if (pos >= lexemes.size()) {
            --pos;
        }
        return;
    }
    else {
        throw std::runtime_error("SYNTAX ERROR\nUnexpected token in line " + std::to_string(lexemes[pos].line_number_ + 1) + ": " + lexemes[pos].value_ + "\nExpected: " + convertTypeToString(other) + ", but got: " + convertTypeToString(lexemes[pos].type_));
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
    }
}

void Parser::function() {
    match(Type::TYPE);
    tfid.declare(lexemes[pos].value_);
    match(Type::IDENTIFIER);
    match(Type::LEFTBRASKET);
    parameters();
    match(Type::RIGHTBRASKET);
    block();
}

void Parser::variable() {
    match(Type::TYPE);
    tid.declare(lexemes[pos].value_);
    match(Type::IDENTIFIER);
    if (lexemes[pos].value_ == "=") {
        match(Type::OPERATOR);
        expression();
        match(Type::DOTXCOMMA);
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
    tid.declare(lexemes[pos].value_);
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
        ifinstruct();
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
    else if (lexemes[pos].value_ == "return") {
        match(Type::KEYWORD);
        expression();
        match(Type::DOTXCOMMA);
        instruction();
    }
    else if (lexemes[pos].value_ == "break" || lexemes[pos].value_ == "continue") {
        match(Type::KEYWORD);
        match(Type::DOTXCOMMA);
        instruction();
    }
    else if (lexemes[pos].type_ == Type::TYPE) {
        variable();
        instruction();
    }
    else if (lexemes[pos].type_ == IDENTIFIER) {
        ooperator();
        instruction();
    }
    else if (lexemes[pos].value_ == "{") {
        block();
        instruction();
    }
    else if (lexemes[pos].value_ == "}") {
        // match(Type::RIGHTFIGUREBRASKET);
        return;
    }
    else {
        throw std::runtime_error("SYNTAX ERROR\nUnexpected token in line " + std::to_string(lexemes[pos].line_number_ + 1) + "\nExpected instruction");
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
    } else {
        match(Type::IDENTIFIER);
        match(Type::OPERATOR);
        expression();
        match(Type::DOTXCOMMA);
    }
}

void Parser::cycle() {
    if (lexemes[pos].type_ == Type::KEYWORD) {
        if (lexemes[pos].value_ == "while") {
            match(Type::KEYWORD);
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
            block();
        } else if (lexemes[pos].value_ == "for") {
            match(Type::KEYWORD);
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
    if (lexemes[pos].type_ == Type::KEYWORD) {
        if (lexemes[pos].value_ == "if") {
            match(Type::KEYWORD);
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
            block();
            if (lexemes[pos].type_ == Type::KEYWORD) {
                if (lexemes[pos].value_ == "else") {
                    match(Type::KEYWORD);
                    block();
                }
            }
        } else if (lexemes[pos].value_ == "switch") {
            match(Type::KEYWORD);
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
            match(Type::LEFTFIGUREBRASKET);
            cases();
            match(Type::RIGHTFIGUREBRASKET);
        } 
    }
}

void Parser::cases() {
    if (lexemes[pos].type_ == Type::KEYWORD) {
        if (lexemes[pos].value_ == "case") {
            match(Type::KEYWORD);
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
        match(Type::STRING);
    } else if (lexemes[pos].type_ == Type::INTEGER) {
        match(Type::INTEGER);
    } else if (lexemes[pos].type_ == Type::FLOAT) {
        match(Type::FLOAT);
    } else if(lexemes[pos].type_ == Type::CHARACTER){
        match(Type::CHARACTER);
    }
    else if (lexemes[pos].type_ == Type::IDENTIFIER) {
        match(Type::IDENTIFIER);
        if (lexemes[pos].type_ == Type::LEFTBRASKET) {
            if (!tfid.isDeclared(lexemes[pos].value_)) {
                throw std::runtime_error("SEMANTICS ERROR\nFunction " + lexemes[pos].value_ + " is not declared in line " + std::to_string(lexemes[pos].line_number_ + 1));
            }
            match(Type::LEFTBRASKET);
            expression();
            match(Type::RIGHTBRASKET);
        } else {
            if (!tid.isDeclared(lexemes[pos - 1].value_)) {
                throw std::runtime_error("SEMANTICS ERROR\nVariable " + lexemes[pos].value_ + " is not declared in line " + std::to_string(lexemes[pos].line_number_ + 1));
            }
        }
    } else if (lexemes[pos].type_ == Type::BOOLEAN) {
        match(Type::BOOLEAN);
    } else if (lexemes[pos].type_ == Type::LEFTBRASKET) {
        match(Type::LEFTBRASKET);
        expression();
        match(Type::RIGHTBRASKET);
    } else {
        if (pos >= lexemes.size()) {
            throw std::runtime_error("SYNTAX ERROR\nInvalid expression in line " + std::to_string(lexemes[pos].line_number_ + 1));
        }
        throw std::runtime_error("SYNTAX ERROR\nInvalid expression in line " + std::to_string(lexemes[pos].line_number_ + 1));
    }
}