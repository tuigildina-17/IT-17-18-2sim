//ѕреобразовать бинарное дерево поиска в двусв€зный список без использовани€
//дополнительной пам€ти(создани€ новых объектов).ѕри преобразовании пол€ left и right
//узлов бинарного дерева рассматриваютс€ эквивалентными пол€м prev и next узлов
//двусв€зного списка.¬ывести исходное дерево и получившийс€ список.Ёлементы в
//результирующем списке должны сохранить свою упор€доченность.

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

//  ласс узла дерева
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

//  ласс бинарного дерева поиска
class BinarySearchTree
{
private:
    TreeNode* root;
    TreeNode* head; // ”казатель на голову двусв€зного списка

    void insert(TreeNode*& node, int value);
    void printTree(TreeNode* node, int space) const;
    void deleteTree(TreeNode* node);
    void inorder(TreeNode* node) const;
    void flatten(TreeNode* node, TreeNode*& prev, TreeNode*& head); // ѕреобразование дерева в двусв€зный список

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int value);
    void printTree() const;
    void inorder() const;

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int min, int max);

    void flatten(); // ѕреобразование в двусв€зный список
    void printList() const; // ѕечать двусв€зного списка
};

void printValues(const vector<int>& values);
int readInt(const string& prompt);

#endif