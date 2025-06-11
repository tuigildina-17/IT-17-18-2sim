//¬ текстовом файле с именем filename дано арифметическое выражение в
//префиксной форме.ќперандами в выражении €вл€ютс€ целые числа из промежутка от 0 до 9.
//»спользуемые операции : сложение(+), вычитание(-), умножение(*), деление нацело(/ ),
//целочисленный остаток от делени€(%) и возведение в степень(^).ѕостройте дерево,
//соответствующее данному выражению.«наки операций кодируйте числами : сложение(-1),
//вычитание(-2), умножение(-3), деление(-4), остаток от делени€(-5), возведение в степень(-6).
//ѕреобразуйте дерево, вычислив значени€ всех поддеревьев, дл€ которых результат
//вычислений €вл€етс€ числом из промежутка от 0 до 9 (замените такие поддеревь€ их
//    значени€ми).¬ыведите указатель на корень полученного дерева.

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <cctype>

using namespace std;

class TNode
{
public:
    int Value;
    TNode* LeftChild;
    TNode* RightChild;

    TNode(int value);

    ~TNode();
};

typedef TNode* PNode;

int TranslateOperator(const string& token);
char GetOperatorSymbol(int operatorCode);
void PrintTree(PNode& rootNode, int level);
int EvaluateTree(PNode rootNode);
PNode BuildTree(const vector<string>& tokens);
void PrintTokens(const vector<string>& tokens);
bool CorrectExpression(const vector<string>& tokens);
PNode TransformTree(PNode rootNode);

#endif