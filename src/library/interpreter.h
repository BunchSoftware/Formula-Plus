#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#pragma once;
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>

namespace Interpreter {

// Операторы для математических выражений
enum class Operator {
    Plus, Minus, Mul, Div, LParen, RParen, UPlus, UMinus, Procent,
    Exponentiation, Extraction, Factorial, Sin, Cos, Tan, Log, Pi, E,
};

// Inline - ключевое слово для встраивания функции в коде. Ускоряет работу кода, но не всегда
// Преобразование из оператора в wstring - обьемных строка, строковый класс для обьемных символов
inline std::wstring ToString(const Operator &op) {
    static const std::unordered_map<Operator, std::wstring> opmap{
            { Operator::Plus, L"+" }, { Operator::Minus, L"-" },
            { Operator::Mul, L"*" }, { Operator::Div, L"/" },
            { Operator::LParen, L"(" }, { Operator::RParen, L")" },
            { Operator::UPlus, L"u+" }, { Operator::UMinus, L"u-" },
            { Operator::Procent, L"%" }, { Operator:: Exponentiation, L"^" },
            { Operator::Extraction, L"sqrt(" }, { Operator::Factorial, L"!" },
            { Operator::Sin, L"sin(" }, { Operator::Cos, L"cos(" },
            { Operator::Tan, L"tan(" }, { Operator::Log, L"log(" },
            { Operator::Pi, L"π" }, { Operator::E, L"e" },
    };
    try {
         return opmap.at(op);
    } catch (std::exception a) {
        std::cout << a.what() << "1";
    }
}

// Преобразование из double в wstring - обьемных строка, строковый класс для широких символов
inline std::wstring ToString(const double &num) {
    return std::to_wstring(num);
}


// Абстрактная структура TokenVisitor для обработки. Реализация паттерна Посетитель
// Когда использовать данный паттерн?
//  Когда имеется много объектов разнородных классов с разными интерфейсами,
//  и требуется выполнить ряд операций над каждым из этих объектов.
//  Когда классам необходимо добавить одинаковый набор операций без изменения этих классов.
//  Когда часто добавляются новые операции к классам, при этом общая структура классов стабильна и практически не изменяется.

struct TokenVisitor {

    // Посещение всех элеменов в массиве
    template<typename Iter> void VisitAll(Iter first, Iter last) {
        std::for_each(first, last, [this](const auto &token) { token->Accept(*this); });
    }

    virtual ~TokenVisitor() {}
    // Посещение токена с численным значением
    virtual void Visit(double) = 0;
    // Посещение токена с оператором
    virtual void Visit(Operator) = 0;
};

namespace Detail {

struct TokenConcept {
    virtual ~TokenConcept() {}
    // Принимает Token Visitor для получения посещенных мест
    virtual void Accept(TokenVisitor &) const = 0;
    // Преобразование в wstring - широкая строка, строковый класс для широких символов
    virtual std::wstring ToString() const = 0;
    // Равен ли текущий токен другому токену
    virtual bool DispatchEquals(const TokenConcept &) const = 0;
    // Равен ли текущий токен числовому значению в другом токене
    virtual bool EqualsTo(double) const {
        return false;
    }
    // Равен ли текущий токен оператора в другом токене
    virtual bool EqualsTo(Operator) const {
        return false;
    }
};

// Создание типа Token
typedef std::shared_ptr<const TokenConcept> Token;

// Преобразование из Token в wstring - широкая строка, строковый класс для широких символов
inline std::wstring ToString(const Token &token) {
    return token->ToString();
}

// Оператор равенства двух сторон выражения
inline bool operator==(const Token &left, const Token &right) {
    return left->DispatchEquals(*right);
}

// Оператор равенства двух сторон выражения
template<typename T> bool operator==(const Token &left, const T &right) {
    return left->EqualsTo(right);
}

// Главный токен с наследованием TokenConcept
template<typename T> struct GenericToken : TokenConcept {
    GenericToken(T payload) : m_payload(std::move(payload)) {}
    // Принимает Token Visitor для получения посещенных мест
    void Accept(TokenVisitor &visitor) const override {
        visitor.Visit(m_payload);
    }
    // Преобразование в wstring - широкая строка, строковый класс для широких символов
    std::wstring ToString() const override {
        return Interpreter::ToString(m_payload);
    }
     // Равен ли текущий токен числовому значению в другом токене
    bool EqualsTo(T value) const override {
        return value == m_payload;
    }
    // Равен ли текущий токен другому токену
    bool DispatchEquals(const TokenConcept &other) const override {
        return other.EqualsTo(m_payload);
    }

    T m_payload;
};
}

using Detail::Token;

// Создание динамического массива Tokens
typedef std::vector<Token> Tokens;

// Создание токена из оператора
inline Token MakeToken(Operator value) {
    return std::make_shared<Detail::GenericToken<Operator>>(value);
}

// Создание токена из числового значения
inline Token MakeToken(double value) {
    return std::make_shared<Detail::GenericToken<double>>(value);
}

class WithTokensResult {
public:
    // Вернуть результат набора токенов
    Tokens Result() {
        return std::move(m_result);
    }

protected:
    ~WithTokensResult() {}
    // Добавить значение к результату
    template<typename T> void AddToResult(T value) {
        m_result.push_back(MakeToken(value));
    }
    // Добавить токен к набору токенов
    void AddToResult(const Token &value) {
        m_result.push_back(value);
    }

private:
    Tokens m_result;
};


// Преобразование текста в циферные и операторские выражения
namespace Lexer {
namespace Detail {

class Tokenizer : public WithTokensResult {
public:
    void Tokenize(const std::wstring &expression) {
        for(m_current = expression.c_str(); *m_current;) {
            // Является ли символ числом
            if(IsNumber())
                ScanNumber();
            // Является ли символ оператором
            else if(IsOperator())
                ScanOperator();
            // Пропускаем, если является пробелом или неопозноным обьектом
            else
              {
                ++m_current;
              }
        }
    }

private:
     // Является ли символ цифрой
    bool IsNumber() const {
        return iswdigit(*m_current) != 0;
    }
    // Поиск и обработка числовых значений
    void ScanNumber() {
        AddToResult(wcstod(m_current, const_cast<wchar_t **>(&m_current)));
    }

    // Набор операторов
    static auto CharToOperatorMap() {
      static const std::unordered_map<std::wstring, Operator> opmap{
              {  L"+" , Operator::Plus}, { L"-", Operator::Minus},
              {  L"*" , Operator::Mul}, { L"/", Operator::Div},
              {  L"(" , Operator::LParen}, { L")", Operator::RParen},
              {  L"u+", Operator::UPlus}, { L"u-", Operator::UMinus},
              {  L"%" ,  Operator::Procent }, { L"^", Operator:: Exponentiation},
              {  L"sqrt(", Operator::Extraction}, { L"!", Operator::Factorial },
              {  L"sin(", Operator::Sin }, { L"cos(", Operator::Cos },
              {  L"tan(", Operator::Tan }, { L"log(", Operator::Log },
              {  L"π", Operator::Pi }, { L"e", Operator::E },
      };
        try {
        return opmap;
        } catch (std::exception a) {
            std::cout << a.what() << 2;
        }
    }

    // Является ли символ оператором
    bool IsOperator(){
        w_current.push_back(*m_current);
        std::unordered_map<std::wstring, Operator> map = CharToOperatorMap();
        return map.find(w_current) != map.end();
    }

    // Поиск и обработка операторов
    void ScanOperator() {
        AddToResult(CharToOperatorMap().at(w_current));
        w_current.clear();
        ++m_current;
    }

    const wchar_t *m_current = nullptr;
    std::wstring w_current;
};

// Пометка, что оператор унарный
class UnaryOperatorMarker : public TokenVisitor, public WithTokensResult {
private:
    void Visit(double num) override {
        AddToResult(num);
        m_nextCanBeUnary = false;
    }

    void Visit(Operator op) override {
        AddToResult(m_nextCanBeUnary ? TryConvertToUnary(op) : op);
        m_nextCanBeUnary = (op != Operator::RParen);
    }

    // Конвертирование в унарный оператор с проверкой
    static Operator TryConvertToUnary(Operator op) {
        if(op == Operator::Plus) return Operator::UPlus;
        if(op == Operator::Minus) return Operator::UMinus;
        return op;
    }

    bool m_nextCanBeUnary = true;
};
}

// Преобразование строкового значения wstring  в набор токенов
inline Tokens Tokenize(const std::wstring &expression) {
    Detail::Tokenizer tokenizer;
    tokenizer.Tokenize(expression);
    return tokenizer.Result();
}
// Пометка, что операция унарная
inline Tokens MarkUnaryOperators(const Tokens &tokens) {
    Detail::UnaryOperatorMarker marker;
    marker.VisitAll(tokens.cbegin(), tokens.cend());
    return marker.Result();
}
}

namespace Parser {

// Определение приоритетов в математическом выражении
template<typename T> int PrecedenceOf(const T &token) {
    if(token == Operator::UMinus) return 6;
    if(token == Operator::Pi || token == Operator::E) return 5;
    if(token == Operator::Exponentiation || token == Operator::Extraction) return 2;
    if(token == Operator::Mul || token == Operator::Div) return 4;
    if(token == Operator::Sin || token == Operator::Cos || token == Operator::Tan || token == Operator::Log) return 3;
    if(token == Operator::Exponentiation || token == Operator::Extraction) return 2;
    if(token == Operator::Procent) return 1;
    return 0;
}

namespace Detail {

// Сортировочный парсер
class ShuntingYardParser : public TokenVisitor, private WithTokensResult  {
public:
    Tokens Result() {
        PopToOutputUntil([this]() { return StackHasNoOperators(); });
        return WithTokensResult::Result();
    }

private:
    // Посещение каждой части выражения и распределение операторов в правильном приоритете
    void Visit(Operator op) override {
        switch(op) {
            case Operator::UPlus:
                break;
            case Operator::UMinus:
            case Operator::LParen:
                PushCurrentToStack(op);
                break;
            case Operator::RParen:
                  if(UnaryOnTop() && isUnary == false)
                  {
                     isUnary = true;
                     break;
                  }
                  else if(m_stack.back() == Operator::RParen)
                  {
                      isUnary = true;
                      break;
                  }
                  else
                  {
                    PopToOutputUntil([this]() { return LeftParenOnTop(); });
                    PopLeftParen();
                    break;
                  }
            default:
                PopToOutputUntil([this, op]() { return LeftParenOnTop() || OperatorWithLessPrecedenceOnTop(op); });
                PushCurrentToStack(op);
                break;
        }
    }

    void Visit(double num) override {
        AddToResult(num);
    }
    // Проверка на закрывающиюся скобку
    bool StackHasNoOperators() const {
        if(m_stack.back() == Operator::LParen) throw std::logic_error("Закрывающая скобка не найдена..");
        return false;
    }
    // Добавление оператора в текущий массив действий
    void PushCurrentToStack(Operator op) {
        m_stack.push_back(MakeToken(op));
    }
    // Проверка на открывающиеся скобку
    void PopLeftParen() {
        if(m_stack.empty() || !LeftParenOnTop()) throw std::logic_error("Открывающая скобка не найдена.");
        m_stack.pop_back();
    }
    // Оператор с меньшим приоритетом сверху
    bool OperatorWithLessPrecedenceOnTop(Operator op) const {
        return PrecedenceOf(m_stack.back()) < PrecedenceOf(op);
    }
    // Левая скобка сверху
    bool LeftParenOnTop() const {
        return m_stack.back() == Operator::LParen;
    }
    bool UnaryOnTop() const {
        if(std::find(m_stack.begin(), m_stack.end(), Operator::Sin) != m_stack.end() ||
           std::find(m_stack.begin(), m_stack.end(), Operator::Cos) != m_stack.end() ||
           std::find(m_stack.begin(), m_stack.end(), Operator::Tan) != m_stack.end() ||
           std::find(m_stack.begin(), m_stack.end(), Operator::Log) != m_stack.end() ||
           std::find(m_stack.begin(), m_stack.end(), Operator::Extraction) != m_stack.end())
           return true;
        else
          return false;
    }
    // Выталкивание в выходной поток до тех пор, либо на его вершине не встретится скобка, или оператор с более низким приоритетом.
    template <typename T>
    void PopToOutputUntil(T whenToEnd) {
        while(!m_stack.empty() && !whenToEnd()) {
            AddToResult(m_stack.back());
            m_stack.pop_back();
        }
    }

    bool isUnary = false;
    Tokens m_stack;
};
}
// Преобразование набора токенов в набор токенов
inline Tokens Parse(const Tokens &tokens) {
    Detail::ShuntingYardParser parser;
    parser.VisitAll(tokens.cbegin(), tokens.cend());
    return parser.Result();
}
}

namespace Evaluator {
namespace Detail {

// Преобразование набора токенов в математическое выражение
class StackEvaluator : public TokenVisitor {
public:
    double Result() const {
        return m_stack.empty() ? 0.0 : m_stack.back();
    }

private:
    typedef std::vector<double> OpStack;
    typedef OpStack::const_iterator Args;

    template<typename T> static auto MakeEvaluator(const size_t arity, T function) {
        return [=](OpStack &stack) {
            if(stack.size() < arity) throw std::logic_error("Недостаточно аргументов в стеке.");
            Args argumentsOnStack = stack.cend() - arity;
            double result = function(argumentsOnStack);
            stack.erase(argumentsOnStack, stack.cend());
            stack.push_back(result);
        };
    }
    // Обработка оператора при сложении двух переменных в математических выражениях
    void Visit(Operator op) override {
        const static std::unordered_map<Operator, std::function<void(OpStack &)>> evaluators{
                { Operator::Plus, MakeEvaluator(2, [=](Args a) { return a[0] + a[1]; }) },
                { Operator::Minus, MakeEvaluator(2, [=](Args a) { return a[0] - a[1]; }) },
                { Operator::Mul, MakeEvaluator(2, [=](Args a) { return a[0] * a[1]; }) },
                { Operator::Div, MakeEvaluator(2, [=](Args a) { return a[0] / a[1]; }) },
                { Operator::Procent, MakeEvaluator(1, [=](Args a) { return a[0]/100; }) },
                { Operator::Exponentiation, MakeEvaluator(2, [=](Args a) { return pow(a[0], a[1]); }) },
                { Operator::Extraction, MakeEvaluator(1, [=](Args a) { return sqrt(a[0]); }) },
                { Operator::Sin, MakeEvaluator(1, [=](Args a) {return sin(a[0]); }) },
                { Operator::Cos, MakeEvaluator(1, [=](Args a) { return cos(a[0]); }) },
                { Operator::Tan, MakeEvaluator(1, [=](Args a) { return tan(a[0]); }) },
                { Operator::Log, MakeEvaluator(1, [=](Args a) { return log(a[0]); }) },
                { Operator::Pi, MakeEvaluator(0, [=](Args a) { return 3.14159265358979323846; }) },
                { Operator::E, MakeEvaluator(0, [=](Args a) { return  2.71828182845904523536; }) }
        };
        try {
            evaluators.at(op)(m_stack);
        } catch (std::exception a) {
            std::cout << a.what() << 3;
        }
    }
    // Обработка числового значения в математических выражениях
    void Visit(double num) override {
        m_stack.push_back(num);
    }

    OpStack m_stack;
};
}

// Оценка набора токенов для преобразования в результат в виде числового значения
inline double Evaluate(const Tokens &tokens) {
    Detail::StackEvaluator evaluator;
    evaluator.VisitAll(tokens.cbegin(), tokens.cend());
    return evaluator.Result();
}
}

// Интерпретировать строковое выражение в числовое значение
inline double InterpreteExperssion(const std::wstring &expression) {
    return Evaluator::Evaluate(Parser::Parse(Lexer::MarkUnaryOperators(Lexer::Tokenize(expression))));
}
}

#endif // INTERPRETER_H
