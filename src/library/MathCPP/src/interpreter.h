#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <format>
#include <string>

#define M_PI 3.14159265358979323846
#define M_E 2.71828182845904523536

namespace Interpreter 
{
	namespace Detail
	{
        typedef std::vector<double> OpStack;
        typedef OpStack::const_iterator Args;

        enum TypeNode {
            Operator,
            OperatorUnary,
            Constant,
            Function,
            Variable
        };

        struct Node {
        public:
            Node(std::wstring operation, TypeNode typeNode, int precedence, std::function<void(OpStack&)> args)
            {
                this->operation = operation;
                this->typeNode = typeNode;
                this->precedence = precedence;
                this->args = args;
            }

            std::wstring operation;
            TypeNode typeNode;
            int precedence;
            std::function<void(OpStack&)> args;
        };

        template<typename T> static auto MakeEvaluator(const size_t arity, T function) {
            return [=](OpStack& stack) {
                if (stack.size() < arity) throw std::logic_error("Недостаточно аргументов в стеке.");
                Args argumentsOnStack = stack.cend() - arity;
                double result = function(argumentsOnStack);
                stack.erase(argumentsOnStack, stack.cend());
                stack.push_back(result);
                };
        }

        // Список математических операций
        const static std::vector<Node*> nodes
        {
            new Node(L"+", TypeNode::Operator, 0, MakeEvaluator(2, [=](Args a) { return a[0] + a[1]; })),
            new Node(L"-", TypeNode::Operator, 0, MakeEvaluator(2, [=](Args a) { return a[0] - a[1]; })),
            new Node(L"u+", TypeNode::OperatorUnary, 9, MakeEvaluator(1, [=](Args a) { return a[0]; })),
            new Node(L"u-", TypeNode::OperatorUnary, 9, MakeEvaluator(1, [=](Args a) { return -a[0]; })),
            new Node(L"*", TypeNode::Operator, 6, MakeEvaluator(2, [=](Args a) { return a[0] * a[1]; })),
            new Node(L"/", TypeNode::Operator, 6, MakeEvaluator(2, [=](Args a) { return a[0] / a[1]; })),
            new Node(L"(", TypeNode::Operator, 0, nullptr),
            new Node(L")", TypeNode::Operator, 0, nullptr),
            new Node(L"%", TypeNode::Operator, 5, MakeEvaluator(1, [=](Args a) { return a[0] / 100; })),
            new Node(L"!", TypeNode::Operator, 7, nullptr),
            new Node(L"=", TypeNode::Operator, -2, MakeEvaluator(2, [=](Args a)
                   {
                        //throw std::logic_error("Ответ уравнения: Решений нет");
                        return a[1]/a[0];
                   })),
            new Node(L"x", TypeNode::Variable, -1, MakeEvaluator(1, [=](Args a) { return a[0]; })),
            new Node(L"^", TypeNode::Operator, 7, MakeEvaluator(2, [=](Args a) { return pow(a[0], a[1]); })),
            new Node(L"sin(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) {return sin(a[0] / 180 * M_PI); })),
            new Node(L"cos(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) { return cos(a[0] / 180 * M_PI); })),
            new Node(L"tan(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) { return tan(a[0] / 180 * M_PI); })),
            new Node(L"cot(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) { return cos(a[0] / 180 * M_PI) / sin(a[0] / 180 * M_PI); })),
            new Node(L"log(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) { return log10l(a[0]); })),
            new Node(L"ln(", TypeNode::Function, 8, MakeEvaluator(1, [=](Args a) { return log(a[0]); })),
            new Node(L"sqrt(", TypeNode::Function, 7, MakeEvaluator(1, [=](Args a) { return sqrt(a[0]); })),
            new Node(L"e", TypeNode::Constant, 10,  MakeEvaluator(0, [=](Args a) { return M_E; })),
            new Node(L"pi", TypeNode::Constant, 10,  MakeEvaluator(0, [=](Args a) { return M_PI; })),
        };

        struct TokenVisitor {

            // Посещение всех элеменов в массиве
            template<typename Iter> void VisitAll(Iter first, Iter last) {
                std::for_each(first, last, [this](const auto& token) { token->Accept(*this); });
            }

            virtual ~TokenVisitor() {}
            // Посещение токена с численным значением
            virtual void Visit(double) = 0;
            // Посещение токена с операцией
            virtual void Visit(Node) = 0;
        };
        struct TokenConcept {
            virtual ~TokenConcept() {}
            // Принимает Token Visitor для получения посещенных мест
            virtual void Accept(TokenVisitor&) const = 0;
            // Преобразование в wstring - широкая строка, строковый класс для широких символов
            virtual std::wstring ToString() const = 0;
        };

        // Создание типа Token
        typedef std::shared_ptr<const TokenConcept> Token;

        inline std::wstring ToString(const Node& node) {
            for (int i = 0; i < nodes.size(); i++)
            {
                if (node.operation == nodes[i]->operation)
                    return node.operation;
            }
        }
        inline std::wstring ToString(const double& num) {
            return std::to_wstring(num);
        }       


        template<typename T> struct GenericToken : TokenConcept {
            GenericToken(T payload) : m_payload(std::move(payload)) {}
            // Принимает Token Visitor для получения посещенных мест
            void Accept(TokenVisitor& visitor) const override {
                visitor.Visit(m_payload);
            }
            // Преобразование в wstring - широкая строка, строковый класс для широких символов
            std::wstring ToString() const override {
                return Detail::ToString(m_payload);
            }

            T m_payload;
        };
	}

    using namespace Detail;

    // Создание динамического массива Tokens
    typedef std::vector<Token> Tokens;

    // Создание токена из оператора
    inline Token MakeToken(Node value) {
        return std::make_shared<Detail::GenericToken<Node>>(value);
    }

    // Создание токена из числового значения
    inline Token MakeToken(double value) {
        return std::make_shared<Detail::GenericToken<double>>(value);
    }

    inline bool NodeIsFinding(std::wstring operation) 
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->operation == operation)
                return true;
        }
        return false;
    }
    inline Node FindNode(std::wstring operation)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->operation == operation)
                return *nodes[i];
        }
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
        void AddToResult(const Token& value) {
            m_result.push_back(value);
        }

    private:
        Tokens m_result;
    };

    namespace Lexer {
        namespace Detail {

            using namespace Interpreter::Detail;

            class Tokenizer : public WithTokensResult {
            public:
                void Tokenize(const std::wstring& expression) {
                    for (m_current = expression.c_str(); *m_current;) {
                        // Является ли символ числом
                        if (IsNumber())
                            ScanNumber();
                        // Является ли символ оператором
                        else if (IsNode())
                            ScanNode();
                        // Пропускаем, если является пробелом или неопозноным обьектом
                        else
                            m_current++;
                    }
                }

            private:
                // Является ли символ цифрой
                bool IsNumber() const {
                    return iswdigit(*m_current) != 0;
                }
                // Поиск и обработка числовых значений
                void ScanNumber() {
                     AddToResult(wcstod(m_current, const_cast<wchar_t**>(&m_current)));
                }

                // Является ли символ оператором
                bool IsNode()
                {
                    if (m_current[0] != *L" ")
                    {
                        w_current.push_back(*m_current);
                        for (int i = 0; i < w_current.size(); i++)
                        {
                            if (NodeIsFinding(w_current))
                            {
                                m_current++;
                                return true;
                            }
                            else if (NodeIsFinding(w_current) == false)
                            {
                                if (m_current[0] != *L"")
                                    m_current++;
                                else
                                {
                                    std::string exception(w_current.begin(), w_current.end());
                                    setlocale(LC_ALL, "rus");
                                    std::string text = "Неизвестное выражение : " + exception;
                                    throw std::logic_error(text);
                                }
                                w_current.push_back(*m_current);
                            }
                        }
                    }
                    return false;
                }

                // Поиск и обработка операторов
                void ScanNode() {
                    AddToResult(FindNode(w_current));
                    w_current.clear();
                }

                const wchar_t* m_current = nullptr;
                std::wstring w_current;
            };

            // Пометка, что оператор унарный
            class UnaryOperatorMarker : public TokenVisitor, public WithTokensResult {
            private:
                void Visit(double num) override {
                    AddToResult(num);
                    m_nextCanBeUnary = false;
                }
                void Visit(Node node) override {
                    AddToResult(m_nextCanBeUnary ? TryConvertToUnary(node) : node);
                    m_nextCanBeUnary = (node.typeNode != TypeNode::Variable && node.operation != L")");
                }

                // Конвертирование в унарный оператор с проверкой
                static Node TryConvertToUnary(Node node) {
                    if (node.operation == L"-")
                        return FindNode(L"u-");
                    if (node.operation == L"+") 
                        return FindNode(L"u+");
                    return node;
                }

                bool m_nextCanBeUnary = true;
            };
        }

        // Преобразование строкового значения wstring  в набор токенов
        inline Tokens Tokenize(const std::wstring& expression) {
            Detail::Tokenizer tokenizer;
            tokenizer.Tokenize(expression);
            return tokenizer.Result();
        }
        // Пометка, что операция унарная
        inline Tokens MarkUnaryOperators(const Tokens& tokens) {
            Detail::UnaryOperatorMarker marker;
            marker.VisitAll(tokens.cbegin(), tokens.cend());
            return marker.Result();
        }
    }

    namespace Parser {

        // Определение приоритетов в математическом выражении
        inline int PrecedenceOf(Token token) 
        {   
            std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(token) };
            return node->m_payload.precedence;
        }

        namespace Detail {

            // Сортировочный парсер
            class ShuntingYardParser : public TokenVisitor, private WithTokensResult {
            public:
                Tokens Result() {
                    PopToOutputUntil([this]() { return StackHasNoOperators(); });
                    return WithTokensResult::Result();
                }

            private:
                // Посещение каждой части выражения и распределение операторов в правильном приоритете
                void Visit(Node node) override {
                    if (node.operation == L"-" && node.typeNode == TypeNode::OperatorUnary)
                        return;
                    else if (node.operation == L"+" && node.typeNode == TypeNode::OperatorUnary)
                        return;
                    else if (node.operation == L"(" && node.typeNode == TypeNode::Operator)
                    {
                        PushCurrentToStack(node);
                        return;
                    }
                    else if (node.operation == L")" && node.typeNode == TypeNode::Operator)
                    {
                        std::shared_ptr<const GenericToken<Node>> functionFrontNode{ std::dynamic_pointer_cast<const GenericToken<Node>>(m_stack.front()) };
                        std::shared_ptr<const GenericToken<Node>> functionBackNode{ std::dynamic_pointer_cast<const GenericToken<Node>>(m_stack.back()) };
                        if (functionFrontNode->m_payload.typeNode == TypeNode::Function || functionBackNode->m_payload.typeNode == TypeNode::Function)
                        {
                            isPopFunction = false;
                            return;
                        }
                        PopToOutputUntil([this]() { return LeftParenOnTop(); });
                        PopLeftParen();
                        return;
                    }
                    else
                    {
                        PopToOutputUntil([this, node]() { return LeftParenOnTop() || FunctionOnTop() || OperatorWithLessPrecedenceOnTop(node); });
                        PushCurrentToStack(node);
                        return;
                    }
                }

                void Visit(double num) override {
                    AddToResult(num);
                }
                // Проверка на закрывающиюся скобку
                bool StackHasNoOperators() const {
                    std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(m_stack.back()) };                 
                    if (node->m_payload.operation == L"(") throw std::logic_error("Закрывающая скобка не найдена..");
                    return false;
                }
                // Добавление оператора в текущий массив действий
                void PushCurrentToStack(Node node) {
                    if (node.typeNode == TypeNode::Function)
                        isPopFunction = true;
                    m_stack.push_back(MakeToken(node));
                }
                // Проверка на открывающиеся скобку
                void PopLeftParen() {
                    if (m_stack.empty() || !LeftParenOnTop()) throw std::logic_error("Открывающая скобка не найдена.");
                    m_stack.pop_back();
                }
                // Оператор с меньшим приоритетом сверху
                bool OperatorWithLessPrecedenceOnTop(Node node)
                {
                     return PrecedenceOf(m_stack.back()) < PrecedenceOf(MakeToken(node));
                }
                // Левая скобка сверху
                bool LeftParenOnTop() const {
                    std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(m_stack.back()) };
                    return node->m_payload.operation == L"(";
                }
                // Левая скобка сверху
                bool FunctionOnTop() const {
                    std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(m_stack.back()) };
                    return (node->m_payload.typeNode == TypeNode::Function && m_stack.size() > 1) || isPopFunction;
                }
                // Выталкивание в выходной поток до тех пор, либо на его вершине не встретится скобка, или оператор с более низким приоритетом.
                template <typename T>
                void PopToOutputUntil(T whenToEnd) {   
                    while (!m_stack.empty() && !whenToEnd())
                    {
                        AddToResult(m_stack.back());
                        m_stack.pop_back();
                    }
                }

                bool isPopFunction = false;
                Tokens m_stack;
            };
        
            class ShuntingGroupingMethod {
            public:
                Tokens Result(Tokens tokens) 
                {
                    for (int i = 0; i < tokens.size(); i++)
                    {
                        std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(tokens[i]) };
                        if (node != nullptr && node->m_payload.operation == L"=")
                        {
                            isEquation = true;
                            continue;
                        }

                        if (isEquation == false)
                            stackToEqual.push_back(tokens[i]);
                        else if(isEquation)
                            stackAfterEqual.push_back(tokens[i]);
                    }
                    if (isEquation)
                    {
                        for (int i = 0; i < stackToEqual.size() - 1; i++)
                        {
                            std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackToEqual[i]) };
                            std::shared_ptr<const GenericToken<double>> number{ std::dynamic_pointer_cast<const GenericToken<double>>(stackToEqual[i]) };
                            if (node != nullptr)
                            {
                                std::shared_ptr<const GenericToken<double>> numberNext{ std::dynamic_pointer_cast<const GenericToken<double>>(stackToEqual[i+1]) };
                                if (numberNext != nullptr)
                                {
                                    if (stackToEqual.size() - i >= 3)
                                    {
                                        std::shared_ptr<const GenericToken<Node>> nodeAfterNext{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackToEqual[i + 2]) };
                                        if (node->m_payload.operation == L"+" && nodeAfterNext != nullptr && nodeAfterNext->m_payload.typeNode != TypeNode::Variable)
                                        {
                                            stackAfterEqual.push_back(MakeToken(FindNode(L"-")));
                                            stackAfterEqual.push_back(MakeToken(numberNext->m_payload));

                                            stackToEqual.erase(stackToEqual.begin()+i);
                                            stackToEqual.erase(stackToEqual.begin()+i);

                                            i -= 1;
                                        }
                                        else if (node->m_payload.operation == L"-" && nodeAfterNext != nullptr && nodeAfterNext->m_payload.typeNode != TypeNode::Variable)
                                        {
                                            stackAfterEqual.push_back(MakeToken(FindNode(L"+")));
                                            stackAfterEqual.push_back(MakeToken(numberNext->m_payload));

                                            stackToEqual.erase(stackToEqual.begin() + i);
                                            stackToEqual.erase(stackToEqual.begin() + i);

                                            i -= 1;
                                        }
                                    }
                                    else 
                                    {
                                        if (node->m_payload.operation == L"+")
                                        {
                                            stackAfterEqual.push_back(MakeToken(FindNode(L"-")));
                                            stackAfterEqual.push_back(MakeToken(numberNext->m_payload));

                                            stackToEqual.erase(stackToEqual.begin() + i);
                                            stackToEqual.erase(stackToEqual.begin() + i);
                                            i -= 1;
                                        }
                                        else if (node->m_payload.operation == L"-")
                                        {
                                            stackAfterEqual.push_back(MakeToken(FindNode(L"+")));
                                            stackAfterEqual.push_back(MakeToken(numberNext->m_payload));

                                            stackToEqual.erase(stackToEqual.begin() + i);
                                            stackToEqual.erase(stackToEqual.begin() + i);

                                            i -= 1;
                                        }
                                    }
                                }
                            }
                            else if (number != nullptr)
                            {
                                std::shared_ptr<const GenericToken<Node>> nodeNext{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackToEqual[i + 1]) };
                                if (nodeNext->m_payload.typeNode == TypeNode::Variable)
                                    i++;
                                else 
                                {
                                    if (nodeNext->m_payload.operation == L"+")
                                    {
                                        stackAfterEqual.push_back(MakeToken(FindNode(L"-")));
                                        stackAfterEqual.push_back(MakeToken(number->m_payload));

                                        stackToEqual.erase(stackToEqual.begin()+i);
                                        stackToEqual.erase(stackToEqual.begin()+i);

                                        i -= 1;
                                    }
                                    else if (nodeNext->m_payload.operation == L"-")
                                    {
                                        stackAfterEqual.push_back(MakeToken(FindNode(L"+")));
                                        stackAfterEqual.push_back(MakeToken(number->m_payload));

                                        stackToEqual.erase(stackToEqual.begin() + i);
                                        stackToEqual.erase(stackToEqual.begin() + i);

                                        i -= 1;
                                    }
                                }
                            }
                        }
                        for (int i = 0; i < stackAfterEqual.size() - 1; i++)
                        {
                            std::shared_ptr<const GenericToken<Node>> node{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackAfterEqual[i]) };
                            std::shared_ptr<const GenericToken<double>> number{ std::dynamic_pointer_cast<const GenericToken<double>>(stackAfterEqual[i]) };
                            if (node != nullptr)
                            {
                                std::shared_ptr<const GenericToken<double>> numberNext{ std::dynamic_pointer_cast<const GenericToken<double>>(stackAfterEqual[i + 1]) };
                                if (numberNext != nullptr)
                                {
                                    if (stackAfterEqual.size() - i >= 3)
                                    {
                                        std::shared_ptr<const GenericToken<Node>> nodeAfterNext{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackAfterEqual[i + 2]) };
                                        if (node->m_payload.operation == L"+" && nodeAfterNext != nullptr && nodeAfterNext->m_payload.typeNode == TypeNode::Variable)
                                        {
                                            stackToEqual.push_back(MakeToken(FindNode(L"-")));
                                            stackToEqual.push_back(MakeToken(numberNext->m_payload));
                                            stackToEqual.push_back(MakeToken(nodeAfterNext->m_payload));

                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);
                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);

                                            i -= 1;
                                        }
                                        else if (node->m_payload.operation == L"-" && nodeAfterNext != nullptr && nodeAfterNext->m_payload.typeNode == TypeNode::Variable)
                                        {
                                            stackToEqual.push_back(MakeToken(FindNode(L"+")));
                                            stackToEqual.push_back(MakeToken(numberNext->m_payload));
                                            stackToEqual.push_back(MakeToken(nodeAfterNext->m_payload));

                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);
                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);

                                            i -= 1;
                                        }
                                    }
                                    else
                                    {
                                        if (node->m_payload.operation == L"+")
                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);
                                        else if (node->m_payload.operation == L"-")
                                            stackAfterEqual.erase(stackAfterEqual.begin() + i);
                                    }
                                }
                            }
                            else if (number != nullptr)
                            {
                                std::shared_ptr<const GenericToken<Node>> nodeNext{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackAfterEqual[i + 1]) };
                                if (nodeNext->m_payload.typeNode == TypeNode::Variable)
                                {
                                    stackToEqual.push_back(MakeToken(FindNode(L"-")));
                                    stackToEqual.push_back(MakeToken(number->m_payload));
                                    stackToEqual.push_back(MakeToken(nodeNext->m_payload));

                                    stackAfterEqual.erase(stackAfterEqual.begin() + i);
                                    stackAfterEqual.erase(stackAfterEqual.begin() + i);

                                    if (i > 0)
                                    {
                                        std::shared_ptr<const GenericToken<Node>> nodePrevios{ std::dynamic_pointer_cast<const GenericToken<Node>>(stackAfterEqual[i - 1]) };
                                        if (nodePrevios != nullptr)
                                        {
                                            stackAfterEqual.erase(stackAfterEqual.begin() + (i - 1));
                                            continue;
                                        }
                                    }         

                                    if (stackAfterEqual.size() != i)
                                        stackAfterEqual.erase(stackAfterEqual.begin() + i);

                                    i -= 1;
                                }
                                else
                                    i++;
                            }
                        }

                        for (int i = 0; i < stackToEqual.size(); i++)
                        {
                            result.push_back(stackToEqual[i]);
                        }

                        result.push_back(MakeToken(FindNode(L"=")));

                        for (int i = 0; i < stackAfterEqual.size(); i++)
                        {
                            result.push_back(stackAfterEqual[i]);
                        }

                        return result;
                    }
                    else
                        return tokens;
                }
            private:
                bool isEquation = false;
                Tokens stackToEqual;
                Tokens stackAfterEqual;
                Tokens result;
            };
        }
        // Преобразование набора токенов в набор токенов
        inline Tokens Parse(Tokens tokens) {
            Detail::ShuntingGroupingMethod gropingMethod;
            Detail::ShuntingYardParser parser;
            Tokens tokensGroup = gropingMethod.Result(tokens);
            parser.VisitAll(tokensGroup.cbegin(), tokensGroup.cend());
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

                // Решаем математическое выражение
                void Visit(Node node) override {                   
                    node.args(m_stack);
                }
                // Обработка числового значения в математических выражениях
                void Visit(double num) override {
                    m_stack.push_back(num);
                }

                OpStack m_stack;
            };
        }

        // Оценка набора токенов для преобразования в результат в виде числового значения
        inline double Evaluate(const Tokens& tokens) {
            Detail::StackEvaluator evaluator;
            evaluator.VisitAll(tokens.cbegin(), tokens.cend());
            return evaluator.Result();
        }
    }

    // Интерпретировать строковое выражение в числовое значение
    inline double InterpreteExperssion(const std::wstring& expression) {
        return Evaluator::Evaluate(Parser::Parse(Lexer::MarkUnaryOperators(Lexer::Tokenize(expression))));
    }
}