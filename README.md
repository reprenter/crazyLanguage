# crazyLanguage
Our full new programming language



Данная документация предназначена для описания базовой версии языка C++. Она включает в себя краткое описание всех частей интерпретатора, формальную грамматику языка и описание структуры проекта.

## Части интерпретатора

Интерпретатор языка C++ состоит из четырёх основных компонентов:

### Лексический анализатор
Лексический анализатор (лексер) отвечает за разбиение исходного кода на токены. Он считывает входной текст и преобразует его в последовательность токенов, которые являются основными единицами синтаксиса. Например, выражение `int x = 10;` будет разбито на токены: `int`, `x`, `=`, `10`, `;`.

В файле присутствуют методы:
```cpp
bool isType(Lexeme lex); // проверка не тип ли эта лексема
bool isLetter(char c); // проверка на букву
bool isOp(char word); // проверка на оператор
std::string Slise(std::string a, int b, int c); // "нарезка" строки
std::vector<Lexeme> AnalyzeLexeme(); // общая функция, запускающая процесс
```

Для проведения лексического анализа необходимо просто запустить AnalyzeLexeme(), она и считает и распределит лексемы по типам

```cpp
enum Type {
    KEYWORD, // base
    IDENTIFIER, // base
    INTEGER, // int
    FLOAT, // float
    STRING, // string with ""
    CHARACTER, // char with ''
    TYPE, // kwords double, int ect.
    BOOLEAN, // true or false kwords
    OPERATOR, // operation kwords
    NONE, // empty
    COMMA, // ,
    LEFTBRASKET, // (
    RIGHTBRASKET, // )    
    LEFTFIGUREBRASKET, // {
    RIGHTFIGUREBRASKET, // }
    LEFTSQUAREBRASKET, // [
    RIGHTSQUAREBRASKET, // ]
    COLON, // :
    DOTXCOMMA // ;
};
```

Так выглядят все типы лексем доступные для обработки и дальнейшего использования.

Также важно отметить, что для хранения лексем используется структура Бор, описанная в отдельных файлах Bor.h и Bor.cpp
```cpp
class BOR {
public:
    struct BorTree {
        bool terminal = false;
        std::map<char, BorTree*> childrens;
    };
    BOR();
    ~BOR();
    BOR(int a);
    void Add(std::string a);
    bool Find(std::string a);
    void Read(std::fstream& f);
private:
    BorTree* head;
};
```
### Синтаксический анализатор
Синтаксический анализатор (парсер) принимает последовательность токенов от лексера и, с помощью алгоритма рекурсивного спуска, строит из них синтаксическое дерево (AST). Он проверяет, соответствует ли последовательность токенов правилам грамматики языка. Также в конструкторе парсера вызывает лексический анализ.

Функции declaration(), variable(), ifinstruct(), cycle() являются обработкой соответсвующего этапа грамматики.

Реализация синтаксического анализатора:

```cpp
class Parser {
public:
	Parser() { AnalyzeLexemes(); }
    void parse() {
        // Логика для построения синтаксического дерева
    }
};
```

Также в parser.cpp есть полезная функция, которая переводит тип из лексера в стандартную строку доступную для вывода
```cpp
std::string convertTypeToString(Type type);
```

### Семантический анализатор
Семантический анализатор проверяет смысловую корректность программы. Он использует информацию из синтаксического дерева и символической таблицы для проверки таких аспектов, как типы переменных и использование функций.

Реализация семантического анализа:

```cpp
class SemanticAnalyzer {
public:
    void analyze(ASTNode* node) {
        // Логика для семантического анализа
    }
};
```

### Интепретатор
Принимает уже обработанный массив токенов и генерирует из них запись ПОЛИЗа и исполняемый код (то есть завершает саму компиляцию)
## Формальная грамматика языка
Примерное описание формальной граммтики языка
```text
S -> Program
Program -> Statement Program | ε
Statement -> Declaration
           | IfStatement
           | WhileStatement
           | ForStatement
           | SwitchStatement
           | Expression ;
Declaration -> Type Identifier [ Identifier ] ;
Type -> int | float | char | string | bool ...
IfStatement -> if ( Expression ) Statement [ else Statement ]
WhileStatement -> while ( Expression ) Statement
ForStatement -> for ( Declaration Expression ; Expression ) Statement
SwitchStatement -> switch ( Expression ) { CaseList }
CaseList -> case Value : Statement [ CaseList ] 
Expression -> ... 
Identifier -> ... 
Value -> ... 
```

## Описание проекта

Проект состоит из трех основных классов: лексера, парсера и семантического анализатора. Каждый класс выполняет свою роль в процессе анализа исходного кода.

Лексический анализатор расписан в виде функций в файлах lexemeanalyzer.h и lexemeanalyzer.cpp
Синтаксический анализатор представлен в виде класса Parser в parser.h и parser.cpp
Семантический в виде класса SemanticsAnalyzer в semantics.h и semantics.cpp
Интерпретатор в виде класса Interpretator в interpretator.h и interpretator.cpp

Классы взаимодействуют следующим образом:

- Лексер считывает исходный код и генерирует токены.
- Парсер принимает токены и строит синтаксическое дерево.
- Семантический анализатор проверяет синтаксическое дерево на наличие семантических ошибок.
- Интерпретатор генерирует ПОЛИЗ и код

Структура классов:

```cpp
class Parser { /* ... */ };
class SemanticAnalyzer { /* ... */ };
class Interpretator { /* ... */ };

int main() {
    Parser parser;
    SemanticAnalyzer semanticAnalyzer;
	Interpretator interpretator;
    // Логика работы интерпретатора
}
```

## Доработка
Данный интерпретатор не может охватить всех аспектов С++, таких как использование библиотек или сторонних файлов, классы и объекто-ориентированное программирование (области видимости и тд)