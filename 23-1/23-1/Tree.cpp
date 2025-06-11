#include "Tree.h"

// ����������� ������ BinarySearchTree (�������������� ������ ������ ��������� nullptr (������ ������))
BinarySearchTree::BinarySearchTree() : root(nullptr), head(nullptr)
{
}

// ���������� ������ BinarySearchTree (������� ��� ���� ������, ������� � �����)
BinarySearchTree::~BinarySearchTree()
{
}

// ����� � ������� ���
void BinarySearchTree::inorder() const 
{
    inorder(root);
}

void BinarySearchTree::inorder(TreeNode* node) const {
    if (node != nullptr) 
    {
        inorder(node->left); // ������� ������� ����� ���������
        cout << node->value << " "; // ����� ������� �������� ����
        inorder(node->right); // � ����� ������� ������ ���������
    }
}

// ����������� ����� ��� �������� ����� ������ (������� ���� � ��� ��� ����������)
void BinarySearchTree::deleteTree(TreeNode* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// ����������� ����� ��� ������� �������� � ������ (��������� �������� � ���������� ������� � ���������)
void BinarySearchTree::insert(TreeNode*& node, int value)
{
    if (!node)
    {
        node = new TreeNode(value);
        return;
    }
    if (value < node->value)
        insert(node->left, value);
    else
        insert(node->right, value);
}

// ����� ��� ������� �������� � ������ � �������������� �����
void BinarySearchTree::insert(int value)
{
    insert(root, value);
}

// ����������� ����� ��� ������ ������
void BinarySearchTree::printTree(TreeNode* node, int space) const
{
    if (!node) return;
    const int indent = 5; // ������� �������
    space += indent;

    printTree(node->right, space); // �������� ������ ���������

    cout << endl;
    for (int i = indent; i < space; i++) cout << ' '; // �������
    cout << node->value << "\n"; // �������� ������� ��������

    printTree(node->left, space); // �������� ����� ���������
}

// ����� ��� ������ ����� ������ � �������������� �����
void BinarySearchTree::printTree() const
{
    if (!root)
    {
        cout << "������ ������\n";
        return;
    }
    printTree(root, 0); // �������� ����������� ����� ������ � ������ ������
}

// ����� ��� ���������� ������ ����������, ���������� ������������� � ����������
void BinarySearchTree::fillFromKeyboard(int count)
{
    cout << "������� " << count << " ����� ����� ����� Enter:\n";
    for (int i = 0; i < count; ++i)
    {
        int val;
        cin >> val;
        insert(val);
    }
}

// ����� ��� ���������� ������ ���������� �� �����
void BinarySearchTree::fillFromFile(const string& filename)
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

// ����� ��� ���������� ������ ���������� ����������
void BinarySearchTree::fillRandom(int count, int min, int max)
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < count; ++i)
    {
        int val = min + rand() % (max - min + 1);
        insert(val);
    }
}

// ������� ��� ������ �������� �� �����
void printValues(const vector<int>& values)
{
    cout << "�������� �����:\n";
    for (int v : values)
    {
        cout << v << " ";
    }
    cout << "\n";
}

// ������� ��� ������ ������ �����
int readInt(const string& prompt)
{
    int val;
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cout << "������ �����. ���������.\n";
            continue;
        }
        stringstream ss(line);
        if (ss >> val)
        {
            char c;
            if (!(ss >> c))
            {
                return val;
            }
        }
        cout << "�������� ����. ������� ����� ����� ��� ������ ��������.\n";
    }
}

// �������������� ������ � ���������� ������
void BinarySearchTree::flatten(TreeNode* node, TreeNode*& prev, TreeNode*& head) 
{
    if (!node) return;

    flatten(node->left, prev, head); // ����������� ����� ������ ���������

    if (!head) 
    {
        head = node; // ��������� ������ ������� ����
    }
    else 
    {
        node->left = prev;   // ��������� prev ��� �������� ����
        prev->right = node;  // ��������� next ��� ����������� ����
    }
    prev = node; // ����������� prev � �������� ����

    flatten(node->right, prev, head); // ����������� ����� ������� ���������
}

void BinarySearchTree::flatten() 
{
    head = nullptr; // ����� ��������� �� ������
    TreeNode* prev = nullptr; // ���������� ����
    flatten(root, prev, head);  // ������ ��������������
}

// ������ ����������� ������
void BinarySearchTree::printList() const 
{
    TreeNode* current = head; // �������� � ������ ������
    cout << "���������� ������: ";
    while (current) 
    {
        cout << current->value << " "; // �������� �������� �������� ����
        current = current->right; // ������� �� ������ � ���������� ����
    }
    cout << endl;
}
