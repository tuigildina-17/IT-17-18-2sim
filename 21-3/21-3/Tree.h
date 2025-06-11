//Дано бинарное дерево и указатель корень дерева P1.Необходимо определить,
//является ли дерево идеально - сбалансированным.В качестве результата вывести логическое
//значение : True или False.Дерево называется идеально - сбалансированным, если для каждой его
//вершины выполнено условие : число вершин ее левого и правого поддерева отличается не
//больше, чем на 1.

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