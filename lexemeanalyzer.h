#include <string>

enum Type {
    KEYWORD,
    IDENTIFIER,
    INTEGER,
    STRING,
    FLOAT,
    CHARACTER,
    BOOLEAN,
    STRING,
    OPERATOR,
    NONE
};

class Lexeme
{
public:
    Lexeme() = default;
    ~Lexeme() = default;

    void AnalyzeLexeme(const std::string& lexeme);
private:
    std::string value_ = "";
    Type type_ = Type::NONE;
    int line_number_ = 0;
    int column_number_ = 0;
};