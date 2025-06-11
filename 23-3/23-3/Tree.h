//������ ������� ��������� ����, ������ ������ �� �������� ������, � �����
//���������� � ��� ����� ������.������ ������ ����� ���������� ����, � ������� ���
//�����������, � ����� ����������������� ������ � ���������������� �������� ����� ����.��
//��������� ��������� ������ ��������� ����������, ����� ���������� ����� ����� �������
//����� ��� ����� ������� ��� ����� ����������� �� ����������.

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <fstream>
#include <random>
#include <map>
#include <set>
#include <functional>
#include <cstdlib>
#include <ctime>

using namespace std;

class TreeNode 
{
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) : value(v), left(nullptr), right(nullptr) 
    {
    }
};

class BinaryTree 
{
private:
    TreeNode* root;
    vector<TreeNode*> overlappedNodes;

    void deleteTree(TreeNode* node);
    void printTree(TreeNode* node, int space) const;

    int cameraPositions(TreeNode* node);


public:
    BinaryTree();
    ~BinaryTree();

    TreeNode* getRoot() const 
    { 
        return root; 
    }

    void insert(int value);
    void printTree() const;

    void fillFromKeyboard();
    bool fillFromFile(const string& filename);
    void fillRandom(int n, int minVal = 0, int maxVal = 100);

    int getOverlapCount() const 
    { 
        return overlapCount; 
    }
    const vector<TreeNode*>& getCameraNodes() const 
    { 
        return cameraNodes; 
    }

    void placeCameras();

    void countCoverage(TreeNode* node);
    void printOverlappedNodes() const;
private:
    vector<TreeNode*> cameraNodes;
    int overlapCount;
};

#endif
