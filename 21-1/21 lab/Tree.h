//���� ������ ������ � ��������� ������ ������ P1.���������� �������
//������������ �������� � ������.������� ������ ����� ��������� �� ������� ����������
//T(n) = O(log n), ��� n - ����� ������ � ������.

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
class BinarySearchTree
{
private:
    TreeNode* root;

    void insert(TreeNode*& node, int value);
    int findMax(TreeNode* node) const;
    void printTree(TreeNode* node, int space) const;
    void deleteTree(TreeNode* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    int findMax() const;
    void printTree() const;

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int min, int max);
};

void printValues(const vector<int>& values);
int readInt(const string& prompt);

#endif