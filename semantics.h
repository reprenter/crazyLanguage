#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "parser.h"

enum NodeType {
    VariableDeclaration,
    VariableUsage,
    Assignment,
    Block
};

struct ASTNode {
    NodeType type;
    std::string varName; // Имя переменной
    std::string varType; // Тип переменной, например "int", "float" и т.д.
    
    ASTNode(NodeType t, const std::string& name, const std::string& type)
        : type(t), varName(name), varType(type) {}
};

class SymbolTable {
public:
    void declareVariable(const std::string& name, const std::string& type) {
        if (symbols.count(name)) {
            throw std::runtime_error("Variable already declared: " + name);
        }
        symbols[name] = type;
    }

    void useVariable(const std::string& name) {
        if (!symbols.count(name)) {
            throw std::runtime_error("Variable not declared: " + name);
        }
    }

    std::string getVariableType(const std::string& name) {
        return symbols[name];
    }

private:
    std::unordered_map<std::string, std::string> symbols; 
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer(SymbolTable& symTable, const std::vector<Lexeme>& lexemes)
      : symbolTable(symTable), lexemes(lexemes), current(0) {}

    void analyze() {
        while (current < lexemes.size()) {
            parseStatement();
        }
    }

private:
    SymbolTable& symbolTable;
    const std::vector<Lexeme>& lexemes;

    size_t current;

    void parseStatement() {
        if (lexemes[current].type_ == KEYWORD && lexemes[current].value_ == "int") {
            parseVariableDeclaration("int");
        } else if (lexemes[current].type_ == KEYWORD && lexemes[current].value_ == "float") {
            parseVariableDeclaration("float");
        } else if (lexemes[current].type_ == IDENTIFIER) {
            parseVariableUsageOrAssignment();
        } else if (lexemes[current].type_ == LEFTFIGUREBRASKET) {
            parseBlock();
        } else {
            throw std::runtime_error("Unexpected token: " + lexemes[current].value_);
        }

        current++;
        
        while (current < lexemes.size() && lexemes[current].type_ == DOTXCOMMA) current++;
        
        if (current < lexemes.size() && lexemes[current].type_ != RIGHTFIGUREBRASKET)
          throw std::runtime_error("Expected ';' or '}'");
      current++;
  }

  void parseVariableDeclaration(const std::string& type) {
      current++; // Skip the type keyword
      if (lexemes[current].type_ != IDENTIFIER) {
          throw std::runtime_error("Expected variable name after type declaration");
      }
      std::string varName = lexemes[current++].value_;
      symbolTable.declareVariable(varName, type);
  }

  void parseVariableUsageOrAssignment() { 
      auto identifierName = lexemes[current++].value_; 
      symbolTable.useVariable(identifierName); 

      if (current < lexemes.size() && lexemes[current].type_ == OPERATOR && 
          lexemes[current].value_ == "=") { 
          current++; // Skip '='
          auto valueExpr = parseExpression(); // Process right-hand side
          // Here you would typically check types for assignment compatibility
      }
  }

  ASTNode* parseBlock() { 
      current++; // Skip '{'
      while(lexemes[current].type_ != RIGHTFIGUREBRASKET){ 
          parseStatement(); 
      } 
      current++;
  }

  ASTNode* parseExpression() { 
       if(lexemes[current].type_ == INTEGER){ 
           return new ASTNode(NodeType::VariableUsage, "", "int"); 
       }else{ 
           return new ASTNode(NodeType::VariableUsage, lexemes[current++].value_, ""); 
       } 
   }
};
