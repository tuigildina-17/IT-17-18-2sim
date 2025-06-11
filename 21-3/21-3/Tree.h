//���� �������� ������ � ��������� ������ ������ P1.���������� ����������,
//�������� �� ������ �������� - ����������������.� �������� ���������� ������� ����������
//�������� : True ��� False.������ ���������� �������� - ����������������, ���� ��� ������ ���
//������� ��������� ������� : ����� ������ �� ������ � ������� ��������� ���������� ��
//������, ��� �� 1.

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <queue>

using namespace std;

// ����� ���� ������
class TreeNode
{
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr)
    {
    }
};

// ����� ��������� ������ ������
class BinaryTree
{
private:
    TreeNode* root;

    void printTree(TreeNode* node, int space) const;
    void deleteTree(TreeNode* node);
    bool isBalanced(TreeNode* node, int& height) const;

public:
    BinaryTree();
    ~BinaryTree();

    void insert(int value);
    void printTree() const;
    bool isBalanced() const;

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int min, int max);
};

void printValues(const vector<int>& values);
int readInt(const string& prompt);

#endif