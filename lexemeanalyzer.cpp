#include "lexemeanalyzer.h"

void Lexeme::AnalyzeLexeme(const std::string& lexeme) {
    try {
        std::stoi(lexeme);
        value_ = lexeme;
        type_ = Type::INTEGER;

    } catch ( ... ) {
        value_ = lexeme;
        type_ = Type::STRING;
    }
}