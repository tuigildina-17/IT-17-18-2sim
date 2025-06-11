#include "Tree.h"

// Конструктор узла дерева
TNode::TNode(int value) : Value(value), LeftChild(nullptr), RightChild(nullptr)
{
}

// Деструктор узла дерева
TNode::~TNode()
{
    delete LeftChild;
    delete RightChild;
}

// Функция для преобразования элемента в код оператора
int TranslateOperator(const string& token)
{
    if (token == "+")
        return -1;
    if (token == "-")
        return -2;
    if (token == "*")
        return -3;
    if (token == "/")
        return -4;
    if (token == "%")
        return -5;
    if (token == "^")
        return -6;
    return
        stoi(token); // Если это не оператор, преобразуем его в целое число и возвращаем
}

// Функция для получения символа оператора по его коду
char GetOperatorSymbol(int operatorCode)
{
    if (operatorCode == -1)
        return '+';
    if (operatorCode == -2)
        return '-';
    if (operatorCode == -3)
        return '*';
    if (operatorCode == -4)
        return '/';
    if (operatorCode == -5)
        return '%';
    if (operatorCode == -6)
        return '^';
    return '?';
}

// Функция для печати дерева выражений
void PrintTree(PNode& rootNode, int level)
{
    if (rootNode != nullptr)
    {
        PrintTree(rootNode->RightChild, level + 1);
        for (int i = 0; i < level; i++)
            cout << setw(4) << ' ';
        if (rootNode->Value < 0)
            cout << setw(4) << GetOperatorSymbol(rootNode->Value) << endl;
        else
            cout << setw(4) << rootNode->Value << endl;
        PrintTree(rootNode->LeftChild, level + 1);
    }
}

// Функция для вычисления значения дерева выражений
int EvaluateTree(PNode rootNode)
{
    if (rootNode->Value >= 0) return rootNode->Value;
    switch (rootNode->Value)
    {
    case -1:
        return EvaluateTree(rootNode->LeftChild) + EvaluateTree(rootNode->RightChild);
    case -2:
        return EvaluateTree(rootNode->LeftChild) - EvaluateTree(rootNode->RightChild);
    case -3:
        return EvaluateTree(rootNode->LeftChild) * EvaluateTree(rootNode->RightChild);
    case -4:
        return EvaluateTree(rootNode->LeftChild) / EvaluateTree(rootNode->RightChild);
    case -5:
        return EvaluateTree(rootNode->LeftChild) % EvaluateTree(rootNode->RightChild);
    case -6:
        return static_cast<int>(pow(EvaluateTree(rootNode->LeftChild), EvaluateTree(rootNode->RightChild)));
    default:
        return 0;
    }
}

// Функция для построения дерева
PNode BuildTree(const vector<string>& tokens)
{
    stack<PNode> nodeStack; // Стек для хранения узлов дерева
    PNode currentNode = nullptr; // Указатель на текущий узел

    // Проходим по элементам в обратном порядке
    for (int i = tokens.size() - 1; i >= 0; --i)
    {
        string token = tokens[i];
        int operatorCode = TranslateOperator(token);// Переводим элемент в код оператора
        currentNode = new TNode(operatorCode); // Создаем новый узел

        if (operatorCode >= 0) // Если число
            nodeStack.push(currentNode); // Заносим в стек
        else // Если оператоp, извлекаем два операнда из стека
        {
            currentNode->LeftChild = nodeStack.top();
            nodeStack.pop();
            currentNode->RightChild = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(currentNode); // Помещаем новый узел обратно в стек
        }
    }
    return nodeStack.top(); // Возвращаем корень дерева (последний оставшийся узел в стеке)
}

// Функция для печати выражения
void PrintTokens(const vector<string>& tokens)
{
    cout << "Выражение: ";
    for (const auto& token : tokens)
    {
        cout << token << " ";
    }
    cout << endl;
}

// Функция для преобразования дерева выражений
PNode TransformTree(PNode rootNode)
{
    if (rootNode == nullptr) return nullptr;

    // Рекурсивно преобразуем левое и правое поддеревья
    rootNode->LeftChild = TransformTree(rootNode->LeftChild);
    rootNode->RightChild = TransformTree(rootNode->RightChild);

    // Если узел — оператор, вычисляем результат поддерева
    if (rootNode->Value < 0)
    {
        int result = EvaluateTree(rootNode);

        // Если результат находится в пределах от 0 до 9, упрощаем узел
        if (result >= 0 && result <= 9)
        {
            delete rootNode->LeftChild;
            delete rootNode->RightChild;
            rootNode->LeftChild = nullptr;
            rootNode->RightChild = nullptr;
            rootNode->Value = result;
        }
    }
    return rootNode;
}

// Функция для проверки корректности выражения
bool CorrectExpression(const vector<string>& tokens)
{
    int numberCount = 0;
    int operatorCount = 0;

    for (const auto& token : tokens)
    {
        if (isdigit(token[0]) && token.size() == 1)
        {
            numberCount++;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^")
        {
            operatorCount++;
        }
        else
        {
            cout << "Ошибка: недопустимый символ '" << token << "'" << endl;
            return false;
        }
    }

    if (numberCount != operatorCount + 1)
    {
        cout << "Ошибка: неверное количество операторов и чисел." << endl;
        return false;
    }

    int stackSize = 0;
    for (int i = tokens.size() - 1; i >= 0; --i)
    {
        const auto& token = tokens[i];
        if (isdigit(token[0]) && token.size() == 1)
        {
            stackSize++;
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^")
        {
            if (stackSize < 2)
            {
                cout << "Ошибка: недостаточно операндов для оператора '" << token << "'" << endl;
                return false;
            }
            stackSize--;
        }
    }
    return true;
}