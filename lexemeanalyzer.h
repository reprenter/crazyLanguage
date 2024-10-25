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

    void SetLineNumber(int line_number) { line_number_ = line_number; };
    void SetColumnNumber(int column_number) { column_number_ = column_number; };
    void SetValue(const std::string value) { value_ = value; };
    void SetType(Type type) { type_ = type; };

    std::string GetValue() const { return value_; };
    Type GetType() const { return type_; };
    int GetLineNumber() const { return line_number_; };
    int GetColumnNumber() const { return column_number_; };
    void AnalyzeLexeme(const std::string& lexeme);
private:
    std::string value_ = "";
    Type type_ = Type::NONE;
    int line_number_ = 0;
    int column_number_ = 0;
};