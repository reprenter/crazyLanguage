#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "semantics.h"

// Глобальный счетчик для меток
int labelCounter = 1;

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

// Функция для перевода лексем в ПОЛИЗ
std::vector<Lexeme> toPolishNotation(const std::vector<Lexeme>& lexemes) {
    std::vector<Lexeme> output; // Вектор для хранения результата
    std::stack<Lexeme> operators; // Стек для операторов
    std::stack<int> loopStartIndices; // Стек для хранения индексов начала циклов
    std::stack<int> loopEndIndices; // Стек для хранения индексов конца циклов
    for (const auto& lexeme : lexemes) {
        if (lexeme.type_ == IDENTIFIER || lexeme.type_ == INTEGER || lexeme.type_ == FLOAT) {
            // Если это операнд, добавляем его в выходной массив
            output.push_back(lexeme);
        } else if (lexeme.type_ == OPERATOR) {
            // Если это оператор, обрабатываем стек
            while (!operators.empty() && precedence(operators.top()) >= precedence(lexeme)) {
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
        } else if (lexeme.type_ == KEYWORD && (lexeme.value_ == "for" || lexeme.value_ == "while")) {
            loopStartIndices.push(output.size()); // Сохраняем индекс начала цикла
            operators.push(lexeme); // Обрабатываем цикл for или while
        } else if (lexeme.type_ == KEYWORD && lexeme.value_ == "if") {
            operators.push(lexeme); // Обрабатываем if
        }
    }

    // Добавляем оставшиеся операторы из стека в выходной массив
    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    // Обработка меток для циклов
    while (!loopStartIndices.empty()) {
        int startIndex = loopStartIndices.top();
        loopStartIndices.pop();

        // Создаем метку для перехода к началу тела цикла
        Lexeme loopLabel;
        loopLabel.value_ = "L" + std::to_string(startIndex); // Пример метки с индексом начала цикла
        loopLabel.type_ = IDENTIFIER; // Используем тип IDENTIFIER для метки

        output.insert(output.begin() + startIndex, loopLabel); // Вставляем метку в выходной массив

        Lexeme jumpToStart;
        jumpToStart.value_ = "goto " + loopLabel.value_; // Создаем команду перехода к началу цикла
        jumpToStart.type_ = KEYWORD; // Используем тип KEYWORD для команды перехода

        output.push_back(jumpToStart); // Добавляем команду перехода в конец выходного массива
    }

    return output; // Возвращаем результат
}
