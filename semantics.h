#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

enum class NodeType {
    Number,
    Variable,
    BinaryOp
};

struct ASTNode {
    NodeType type;
    union {
        int value;                     // Для чисел
        std::string* varName;          // Для переменных
        struct {                       // Для бинарных операций
            ASTNode* left;
            ASTNode* right;
            char op;                   // Оператор: +, -, *, /
        };
    };

    // Конструкторы для различных типов узлов
    ASTNode(int val) : type(NodeType::Number) { value = val; }
    ASTNode(std::string name) : type(NodeType::Variable) { varName = new std::string(name); }
    ASTNode(ASTNode* l, char oper, ASTNode* r) : type(NodeType::BinaryOp) {
        left = l; op = oper; right = r;
    }

    ~ASTNode() {
        if (type == NodeType::Variable) delete varName;
        else if (type == NodeType::BinaryOp) {
            delete left;
            delete right;
        }
    }
};

class SymbolTable {
public:
    void declare(const std::string& name, const std::string& type) {
        if (symbols.count(name)) throw std::runtime_error("Variable already declared");
        symbols[name] = type;
    }

    std::string lookup(const std::string& name) {
        if (!symbols.count(name)) throw std::runtime_error("Variable not declared");
        return symbols[name];
    }

private:
    std::unordered_map<std::string, std::string> symbols;
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer(SymbolTable& symTable) : symbolTable(symTable) {}

    void analyze(ASTNode* node) {
        switch (node->type) {
            case NodeType::Number:
                break;

            case NodeType::Variable:
                // Проверка существования переменной
                symbolTable.lookup(*node->varName);
                break;

            case NodeType::BinaryOp:
                analyze(node->left);
                analyze(node->right);
                checkTypes(node);
                break;

            default:
                throw std::runtime_error("Unknown node type");
        }
    }

private:
    SymbolTable& symbolTable;

    void checkTypes(ASTNode* node) {
        std::string leftType = getType(node->left);
        std::string rightType = getType(node->right);

        if (leftType != rightType)
            throw std::runtime_error("Type mismatch in binary operation");
    }

    std::string getType(ASTNode* node) {
        if (node->type == NodeType::Number) return "int"; // Простой пример с типом int
        if (node->type == NodeType::Variable)
            return symbolTable.lookup(*node->varName);
        
        return "unknown";
    }
};
