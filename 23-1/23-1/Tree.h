//������������� �������� ������ ������ � ���������� ������ ��� �������������
//�������������� ������(�������� ����� ��������).��� �������������� ���� left � right
//����� ��������� ������ ��������������� �������������� ����� prev � next �����
//����������� ������.������� �������� ������ � ������������ ������.�������� �
//�������������� ������ ������ ��������� ���� ���������������.

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
    TreeNode* head; // ��������� �� ������ ����������� ������

    void insert(TreeNode*& node, int value);
    void printTree(TreeNode* node, int space) const;
    void deleteTree(TreeNode* node);
    void inorder(TreeNode* node) const;
    void flatten(TreeNode* node, TreeNode*& prev, TreeNode*& head); // �������������� ������ � ���������� ������

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    void printTree() const;
    void inorder() const;

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int min, int max);

    void flatten(); // �������������� � ���������� ������
    void printList() const; // ������ ����������� ������
};

void printValues(const vector<int>& values);
int readInt(const string& prompt);

#endif