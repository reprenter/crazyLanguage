#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include "parser.h"

std::vector<Lexeme> getPart2(const std::vector<Lexeme>& lexemes, int& i);

// Функция для определения приоритета операторов
int precedence(const Lexeme& lexeme) {
    if (lexeme.type_ == OPERATOR) {
        if (lexeme.value_ == "+" || lexeme.value_ == "-") return 1;
        if (lexeme.value_ == "*" || lexeme.value_ == "/") return 2;
        if (lexeme.value_ == "%") return 2; // Добавлен оператор %
        if (lexeme.value_ == "**") return 3; // Добавлен оператор **
    }
    return 0;
}

std::vector<Lexeme> MicroToPolish(const std::vector<Lexeme>& lexemes, int& i){
    std::vector<Lexeme> output; // Вектор для хранения результата
    std::stack<Lexeme> operators; // Стек для операторов
    for (; i < lexemes.size(); i++) {
        auto& lexeme = lexemes[i];
        if (lexeme.type_ == IDENTIFIER || lexeme.type_ == INTEGER || lexeme.type_ == FLOAT) {
            // Если это операнд, добавляем его в выходной массив
            if(lexemes[i+1].type_ != LEFTBRASKET)
                output.push_back(lexeme);
            else{
                Lexeme name = lexeme;
                while(lexemes[i].type_ != RIGHTBRASKET){
                    i++;
                    std::vector<Lexeme> ARG = getPart2(lexemes, i);
                    for(auto i : ARG){
                        output.push_back(i);
                    }
                    Lexeme comma;
                    comma.type_ = COMMA;
                    comma.value_ = ",";
                    output.push_back(comma);
                }
                output.pop_back();
                output.push_back(name);
            }
        } else if (lexeme.type_ == OPERATOR) {
            // Если это оператор, обрабатываем стек
            while (!operators.empty() && precedence(operators.top()) >= precedence(lexeme) and operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(lexeme); // Добавляем текущий оператор в стек
        } else if (lexeme.type_ == LEFTBRASKET) {
            operators.push(lexeme); // Добавляем открывающую скобку в стек
        } else if (lexeme.type_ == RIGHTBRASKET) {
            while (!operators.empty() && operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Удаляем открывающую скобку
            }
            else{
                break;
            }
        } 
    }
    // Добавляем оставшиеся операторы из стека в выходной массив
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

std::vector<Lexeme> getPart(const std::vector<Lexeme>& lexemes, int& i){
    std::vector<Lexeme> output; // Вектор для хранения результата
    std::stack<Lexeme> operators; // Стек для операторов
    for (; i < lexemes.size(); i++) {
        auto& lexeme = lexemes[i];
        if (lexeme.type_ == IDENTIFIER || lexeme.type_ == INTEGER || lexeme.type_ == FLOAT) {
            // Если это операнд, добавляем его в выходной массив
            if(lexemes[i+1].type_ != LEFTBRASKET)
                output.push_back(lexeme);
            else{
                Lexeme name = lexeme;
                while(lexemes[i].type_ != RIGHTBRASKET){
                    i++;
                    std::vector<Lexeme> ARG = getPart2(lexemes, i);
                    for(auto i : ARG){
                        output.push_back(i);
                    }
                    Lexeme comma;
                    comma.type_ = COMMA;
                    comma.value_ = ",";
                    output.push_back(comma);
                }
                output.pop_back();
                output.push_back(name);
            }
        } else if (lexeme.type_ == OPERATOR) {
            // Если это оператор, обрабатываем стек
            while (!operators.empty() && precedence(operators.top()) >= precedence(lexeme) and operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(lexeme); // Добавляем текущий оператор в стек
        } else if (lexeme.type_ == RIGHTBRASKET) {
            break;
        } else if(lexeme.type_ == DOTXCOMMA or lexeme.type_ == COMMA){
            break;
        } else if(lexeme.type_ == TYPE){
            output.push_back(lexeme);
        }
    }
    // Добавляем оставшиеся операторы из стека в выходной массив
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

std::vector<Lexeme> getPart2(const std::vector<Lexeme>& lexemes, int& i){
    std::vector<Lexeme> output; // Вектор для хранения результата
    std::stack<Lexeme> operators; // Стек для операторов
    for (; i < lexemes.size(); i++) {
        auto& lexeme = lexemes[i];
        if (lexeme.type_ == IDENTIFIER || lexeme.type_ == INTEGER || lexeme.type_ == FLOAT) {
            // Если это операнд, добавляем его в выходной массив
            if(lexemes[i+1].type_ != LEFTBRASKET)
                output.push_back(lexeme);
            else{
                Lexeme name = lexeme;
                while(lexemes[i].type_ != RIGHTBRASKET){
                    i++;
                    std::vector<Lexeme> ARG = getPart2(lexemes, i);
                    for(auto i : ARG){
                        output.push_back(i);
                    }
                    Lexeme comma;
                    comma.type_ = COMMA;
                    comma.value_ = ",";
                    output.push_back(comma);
                }
                output.pop_back();
                output.push_back(name);
            }
        } else if (lexeme.type_ == OPERATOR) {
            // Если это оператор, обрабатываем стек
            while (!operators.empty() && precedence(operators.top()) >= precedence(lexeme) and operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(lexeme); // Добавляем текущий оператор в стек
        } else if (lexeme.type_ == RIGHTBRASKET) {
            break;
        } else if(lexeme.type_ == DOTXCOMMA or lexeme.type_ == COMMA or lexeme.type_ == COLON){
            break;
        } else if(lexeme.type_ == TYPE){
            output.push_back(lexeme);
        }
    }
    // Добавляем оставшиеся операторы из стека в выходной массив
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

std::vector<Lexeme> output; // Вектор для хранения результата
std::stack<Lexeme> operators; // Стек для операторов
std::stack<std::pair<int, std::string>> startIndices; // Стек для хранения индексов начала циклов и условных выражений
std::queue<int> endIndices; // Стек для хранения индексов конца циклов и условных выражений

// Функция для перевода лексем в ПОЛИЗ
std::vector<Lexeme> toPolishNotation(const std::vector<Lexeme>& lexemes) {
    int k = 0, swk = 0;
    std::stack<std::pair<int, std::string>> rigthFigureBrasket;
    std::stack<std::vector<Lexeme>> forLexemes;
    std::stack<std::pair<int, std::vector<Lexeme>>> switchLexemes;
    for (int i = 0; i < lexemes.size(); i++) {
        auto& lexeme = lexemes[i];
        if (lexeme.type_ == IDENTIFIER || lexeme.type_ == INTEGER || lexeme.type_ == FLOAT) {
            // Если это операнд, добавляем его в выходной массив
            if(lexemes[i+1].type_ != LEFTBRASKET)
                output.push_back(lexeme);
            else{
                Lexeme name = lexeme;
                while(lexemes[i].type_ != RIGHTBRASKET){
                    i++;
                    std::vector<Lexeme> ARG = getPart2(lexemes, i);
                    for(auto i : ARG){
                        output.push_back(i);
                    }
                    Lexeme comma;
                    comma.type_ = COMMA;
                    comma.value_ = ",";
                    output.push_back(comma);
                }
                output.pop_back();
                output.push_back(name);
            }
        } else if (lexeme.type_ == OPERATOR) {
            // Если это оператор, обрабатываем стек
            while (!operators.empty() && precedence(operators.top()) >= precedence(lexeme) and operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(lexeme); // Добавляем текущий оператор в стек
        } 
        else if(lexeme.type_ == DOTXCOMMA){
            // Добавляем оставшиеся операторы из стека в выходной массив
            while (!operators.empty()) {
                output.push_back(operators.top());
                operators.pop();
            }
        }
        else if (lexeme.type_ == LEFTBRASKET) {
            operators.push(lexeme); // Добавляем открывающую скобку в стек
        } else if (lexeme.type_ == RIGHTBRASKET) {
            while (!operators.empty() && operators.top().type_ != LEFTBRASKET) {
                output.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop(); // Удаляем открывающую скобку
            }
        } else if (lexeme.type_ == KEYWORD && (lexeme.value_ == "for" || lexeme.value_ == "while" || lexeme.value_ == "if" || lexeme.value_ == "switch" ||
                                                                                                                              lexeme.value_ == "case" ||
                                                                                                                              lexeme.value_ == "break")) {
            Lexeme IF;
            IF.value_ = "if"; // Создаем команду перехода к началу цикла
            IF.type_ = KEYWORD; 
            if(lexeme.value_ == "if"){

                output.push_back(IF);
                i++;
                output.push_back(lexemes[i]);
                Lexeme universal;
                universal.value_ = "!";
                universal.type_ = OPERATOR;
                output.push_back(universal);
                i++;
                std::vector<Lexeme> ADD = MicroToPolish(lexemes, i);
                for(auto f : ADD){
                    output.push_back(f);
                }
                universal.value_ = ")";
                universal.type_ = RIGHTBRASKET;
                output.push_back(universal);
                Lexeme ifLabel;
                ifLabel.value_ = "goto L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                rigthFigureBrasket.emplace(k, "if");
                k++;
                output.push_back(ifLabel);
            }
            else if(lexeme.value_ == "while"){
                Lexeme ifLabel;
                ifLabel.value_ = "L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                rigthFigureBrasket.emplace(k, "whileOpen");
                k++;
                output.push_back(ifLabel);
                output.push_back(IF);
                i++;
                output.push_back(lexemes[i]);
                Lexeme universal;
                universal.value_ = "!";
                universal.type_ = OPERATOR;
                output.push_back(universal);
                i++;
                std::vector<Lexeme> ADD = MicroToPolish(lexemes, i);
                for(auto f : ADD){
                    output.push_back(f);
                }
                universal.value_ = ")";
                universal.type_ = RIGHTBRASKET;
                output.push_back(universal);
                ifLabel.value_ = "goto L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                rigthFigureBrasket.emplace(k, "whileClose");
                k++;
                output.push_back(ifLabel);
            }
            else if(lexeme.value_ == "for"){
                std::vector<Lexeme> ADD = getPart(lexemes, i);
                i++;
                std::vector<Lexeme> IF_ = getPart(lexemes, i);
                i++;
                std::vector<Lexeme> DO = getPart(lexemes, i);

                for(auto j : ADD){
                    output.push_back(j);
                }

                Lexeme ifLabel;
                ifLabel.value_ = "L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                rigthFigureBrasket.emplace(k, "forOpen");
                k++;
                output.push_back(ifLabel);
                output.push_back(IF);
                Lexeme universal;
                universal.value_ = "(";
                universal.type_ = LEFTBRASKET;                
                output.push_back(universal);
                universal.value_ = "!";
                universal.type_ = OPERATOR;
                output.push_back(universal);
                for(auto f : IF_){
                    output.push_back(f);
                }
                universal.value_ = ")";
                universal.type_ = RIGHTBRASKET;
                output.push_back(universal);
                ifLabel.value_ = "goto L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                rigthFigureBrasket.emplace(k, "forClose");
                k++;
                output.push_back(ifLabel);
                forLexemes.push(DO);

            }
            else if(lexeme.value_ == "switch"){
                i++;
                switchLexemes.emplace(swk, getPart(lexemes, i));
                rigthFigureBrasket.emplace(swk, "switchClose");
                swk++;
            }
            else if(lexeme.value_ == "case"){
                output.push_back(IF);
                i++;
                Lexeme universal;
                universal.value_ = "(";
                universal.type_ = LEFTBRASKET; 
                output.push_back(universal);
                universal.value_ = "!";
                universal.type_ = OPERATOR;
                output.push_back(universal);
                for(auto j : switchLexemes.top().second){
                    output.push_back(j);
                }
                std::vector<Lexeme> ARG = getPart2(lexemes, i);
                for(auto j : ARG){
                    output.push_back(j);
                }
                output.emplace_back("=",OPERATOR);
                output.emplace_back(")", RIGHTBRASKET);
                output.emplace_back("goto L"+std::to_string(k), KEYWORD);
                rigthFigureBrasket.emplace(k, "caseClose");
                k++;
                i++;
            }
            else if(lexeme.value_ == "break"){
                continue;
            }
        } else if(lexeme.type_ == RIGHTFIGUREBRASKET){
            if(rigthFigureBrasket.size() == 0) continue;
            if(lexemes.size()>i+1 and lexemes[i+1].value_ == "else" and rigthFigureBrasket.top().second == "if"){
                int _ = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                Lexeme ifLabel;
                ifLabel.value_ = "goto L" + std::to_string(k); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                
                rigthFigureBrasket.emplace(k, "else");
                k++;
                output.push_back(ifLabel);
                ifLabel.value_ = "L" + std::to_string(_); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                output.push_back(ifLabel);
            }
            else if(rigthFigureBrasket.top().second == "if"){
                int _ = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                Lexeme ifLabel;
                ifLabel.value_ = "L" + std::to_string(_); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                output.push_back(ifLabel);
            }
            else if(rigthFigureBrasket.top().second == "else"){
                int _ = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                Lexeme ifLabel;
                ifLabel.value_ = "L" + std::to_string(_); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                output.push_back(ifLabel);
            }
            else if(rigthFigureBrasket.top().second == "whileClose"){
                int _2 = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                int _1 = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();

                Lexeme ifLabel;
                ifLabel.value_ = "goto L" + std::to_string(_1); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                output.push_back(ifLabel);

                ifLabel.value_ = "L" + std::to_string(_2); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                output.push_back(ifLabel);

            }
            else if(rigthFigureBrasket.top().second == "forClose"){
                int _2 = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                int _1 = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();

                Lexeme ifLabel;
                ifLabel.value_ = "goto L" + std::to_string(_1); // Пример метки с индексом начала цикла
                ifLabel.type_ = KEYWORD; // Используем тип KEYWORD для метки
                output.push_back(ifLabel);
                for(auto i : forLexemes.top()){
                    output.push_back(i);
                }
                forLexemes.pop();
                ifLabel.value_ = "L" + std::to_string(_2); // Пример метки с индексом начала цикла
                ifLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки
                output.push_back(ifLabel);
            }
            else if(rigthFigureBrasket.top().second == "switchClose"){
                rigthFigureBrasket.pop();
                output.emplace_back("EXIT"+std::to_string(switchLexemes.top().first), IDENTIFIER);
            }
            else if(rigthFigureBrasket.top().second == "caseClose"){
                int _ = rigthFigureBrasket.top().first;
                rigthFigureBrasket.pop();
                output.emplace_back("goto EXIT"+std::to_string(switchLexemes.top().first), KEYWORD);
                output.emplace_back("L"+std::to_string(_), IDENTIFIER);
            }
        }
        else if(lexeme.type_ == TYPE or lexeme.type_ == KEYWORD){
            output.push_back(lexeme);
        }
    }

    // Добавляем оставшиеся операторы из стека в выходной массив
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output; // Возвращаем результат
}
