//–еализовать дл€ бинарного дерева интерфейс итератора, который будет возвращать
//значени€ элементов, наход€щихс€ в узлах дерева, в пор€дке "лево-право-корень".
//ѕреобразовывать дерево в список или иную структуру данных нельз€, рекурсию использовать
//запрещаетс€

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <random>

using namespace std;

class TreeNode 
{
public:
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val);
};

class BinaryTree 
{
private:
    TreeNode* root;

    void deleteTree(TreeNode* node);

public:
    BinaryTree();
    ~BinaryTree();

    void insert(int value);

    void fillFromKeyboard(int count);
    void fillFromFile(const string& filename);
    void fillRandom(int count, int minVal, int maxVal);

    void printTree() const;

    class PostOrderIterator 
    {
        friend class BinaryTree;

    private:
        stack<TreeNode*> s;
        TreeNode* lastVisited;
        TreeNode* current;

        PostOrderIterator(TreeNode* root);

        void pushLeftMost(TreeNode* node);

    public:
        bool hasNext();
        int next();
    };

    PostOrderIterator getPostOrderIterator() const;
};

void printTreeHelper(TreeNode* node, int space);
void postOrderPushLeftMost(stack<TreeNode*>& s, TreeNode* node);

#endif
