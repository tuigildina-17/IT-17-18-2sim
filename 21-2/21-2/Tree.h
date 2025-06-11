//Дано дерево поиска и указатель корень дерева P1.Необходимо вставить в дерево
//значение X.

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

// Класс узла дерева
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

// Класс бинарного дерева поиска
class BinarySearchTree
{
private:
    TreeNode* root;

    void insert(TreeNode*& node, int value);
    void printTree(TreeNode* node, int space) const;
    void deleteTree(TreeNode* node);

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    void printTree() const;

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int min, int max);
};

void printValues(const vector<int>& values);
int readInt(const string& prompt);

#endif