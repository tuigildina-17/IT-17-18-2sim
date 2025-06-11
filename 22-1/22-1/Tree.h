//� ��������� ����� � ������ filename ���� �������������� ��������� �
//���������� �����.���������� � ��������� �������� ����� ����� �� ���������� �� 0 �� 9.
//������������ �������� : ��������(+), ���������(-), ���������(*), ������� ������(/ ),
//������������� ������� �� �������(%) � ���������� � �������(^).��������� ������,
//��������������� ������� ���������.����� �������� ��������� ������� : ��������(-1),
//���������(-2), ���������(-3), �������(-4), ������� �� �������(-5), ���������� � �������(-6).
//������������ ������, �������� �������� ���� �����������, ��� ������� ���������
//���������� �������� ������ �� ���������� �� 0 �� 9 (�������� ����� ���������� ��
//    ����������).�������� ��������� �� ������ ����������� ������.

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