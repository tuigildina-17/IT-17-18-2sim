#include "Tree.h"

TreeNode::TreeNode(int val) : value(val), left(nullptr), right(nullptr) 
{
}

BinaryTree::BinaryTree() : root(nullptr) 
{
}

BinaryTree::~BinaryTree() 
{
    deleteTree(root);
}

void BinaryTree::deleteTree(TreeNode* node) 
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BinaryTree::insert(int value) 
{
    if (!root) 
    {
        root = new TreeNode(value);
        return;
    }

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) 
    {
        TreeNode* current = q.front();
        q.pop();

        if (!current->left) 
        {
            current->left = new TreeNode(value);
            return;
        }
        else 
        {
            q.push(current->left);
        }

        if (!current->right) 
        {
            current->right = new TreeNode(value);
            return;
        }
        else 
        {
            q.push(current->right);
        }
    }
}

void BinaryTree::fillFromKeyboard(int count) 
{
    cout << "������� " << count << " �����:\n";
    for (int i = 0; i < count; ++i) {
        int val; cin >> val;
        insert(val);
    }
}

void BinaryTree::fillFromFile(const string& filename) 
{
    ifstream fin(filename);
    if (!fin.is_open()) 
    {
        cout << "�� ������� ������� ���� " << filename << "\n";
        return;
    }
    int val;
    while (fin >> val) 
    {
        insert(val);
    }
    fin.close();
}

void BinaryTree::fillRandom(int count, int minVal, int maxVal) 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(minVal, maxVal);

    for (int i = 0; i < count; ++i) 
    {
        insert(dis(gen));
    }
}

void BinaryTree::printTree() const 
{
    if (!root) 
    {
        cout << "������ ������\n";
        return;
    }
    printTreeHelper(root, 0);
}

void printTreeHelper(TreeNode* node, int space) 
{
    if (!node) return;
    const int indent = 5;
    space += indent;

    printTreeHelper(node->right, space);

    cout << endl;
    for (int i = indent; i < space; ++i)
        cout << ' ';
    cout << node->value << "\n";

    printTreeHelper(node->left, space);
}

// �������� � ���� ��� ���� �� ������ ���� ������� � node
void postOrderPushLeftMost(stack<TreeNode*>& s, TreeNode* node) 
{
    while (node) 
    {
        s.push(node); // ����� ������� ���� � ����
        node = node->left; // ��������� � ������ �������
    }
}

// ����������� ��������� ������������ ������
BinaryTree::PostOrderIterator::PostOrderIterator(TreeNode* root) : lastVisited(nullptr), current(root) 
{
    pushLeftMost(current); // ����� � ���� ��� ����� ����� ������� � �����
}

// ��������������� ����� ��������� ��� ��������� � ���� ����� ����� ������� � node
void BinaryTree::PostOrderIterator::pushLeftMost(TreeNode* node) 
{
    postOrderPushLeftMost(s, node);
}

// ���������, ���� �� ��� �������� ��� ������ � ����������� �������
bool BinaryTree::PostOrderIterator::hasNext() 
{
    return !s.empty(); // ���������� true, ���� ���� �� ���� � ������ ���� ��� ���� ��� ���������
}

// ���������� ��������� ������� � ����������� ������
int BinaryTree::PostOrderIterator::next() 
{
    while (!s.empty()) 
    {
        TreeNode* peekNode = s.top();

        // ���� ������ ������� ���������� � �� ��� ��� �� ��������
        if (peekNode->right && lastVisited != peekNode->right) 
        {
            pushLeftMost(peekNode->right); // ��������� � ���� (����� � ���� ��� ����� �����)
        }
        else  // ������ ������� ����������� ��� ��� ������� � ����� ���������� ������� ����
        {
            s.pop();
            lastVisited = peekNode; // ���������� ��������� ���������� ����
            return peekNode->value; // ���������� �������� ����
        }
    }
    // ���� ���� ���� - ����� ��������, ���������� ��������� ���
    throw out_of_range("������ ��� ���������");
}

// ������ � ���������� �������� ��� ������������ ������ �������� ������
BinaryTree::PostOrderIterator BinaryTree::getPostOrderIterator() const 
{
    return PostOrderIterator(root);
}