#include "Tree.h"

// ����������� ������ BinaryTree (�������������� ������ ������ ��������� nullptr (������ ������))
BinaryTree::BinaryTree() : root(nullptr)
{
}

// ���������� ������ BinaryTree (������� ��� ���� ������, ������� � �����)
BinaryTree::~BinaryTree()
{
    deleteTree(root);
}

// ����������� ����� ��� �������� ����� ������ (������� ���� � ��� ��� ����������)
void BinaryTree::deleteTree(TreeNode* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


// ����� ��� ������� �������� � ������
void BinaryTree::insert(int value)
{
    if (!root) 
    {
        root = new TreeNode(value);
        return;
    }

    // ���������� ������� ��� ������ ������� ���������� �����
    queue<TreeNode*> q;
    q.push(root); // �������� � �����

    while (!q.empty()) 
    {
        TreeNode* current = q.front(); // ����� ���� �� ������ �������
        q.pop(); // ������� ������ �� �������

        // ��������� ����� ���������
        if (!current->left) 
        {
            current->left = new TreeNode(value);
            return;
        }
        else {
            q.push(current->left);
        }

        // ��������� ������ ���������
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

// ����������� ����� ��� ������ ������
void BinaryTree::printTree(TreeNode* node, int space) const
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
void BinaryTree::printTree() const
{
    if (!root)
    {
        cout << "������ ������\n";
        return;
    }
    printTree(root, 0); // �������� ����������� ����� ������ � ������ ������
}

// ����� ��� ��������, �������� �� ������ �������� ����������������
bool BinaryTree::isBalanced() const
{
    int height = 0; // ���������� ��� ������
    return isBalanced(root, height); // // ����� ���������������� ������ � ������ ������
}

// ��������������� ����� ��� �������� ������������������ ������
bool BinaryTree::isBalanced(TreeNode* node, int& height) const
{
    if (!node)
    {
        height = 0; // ��� ������� ���� ������ 0
        return true; // ������ ������ ��������������
    }

    // ���������� ��� �������� ����� ������ � ������� �����������
    int leftHeight = 0, rightHeight = 0;

    // ���������� ��������� ����� � ������ ����������
    bool leftBalanced = isBalanced(node->left, leftHeight);
    bool rightBalanced = isBalanced(node->right, rightHeight);

    // ������ �������� ���� ����� ������������ ������ ��� ����������� ���� 1 (��� ������ ����)
    height = max(leftHeight, rightHeight) + 1;

    // ���������� true, ���� ��� ��������� �������������� � ������� �� ����� �� ��������� 1
    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}

// ����� ��� ���������� ������ ����������, ���������� ������������� � ����������
void BinaryTree::fillFromKeyboard(int count)
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

// ����� ��� ���������� ������ ���������� ����������
void BinaryTree::fillRandom(int count, int min, int max)
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