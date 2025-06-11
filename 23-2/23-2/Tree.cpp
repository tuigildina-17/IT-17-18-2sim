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
    cout << "Введите " << count << " чисел:\n";
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
        cout << "Не удалось открыть файл " << filename << "\n";
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
        cout << "Дерево пустое\n";
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

// Помещает в стек все узлы по левому пути начиная с node
void postOrderPushLeftMost(stack<TreeNode*>& s, TreeNode* node) 
{
    while (node) 
    {
        s.push(node); // Кладём текущий узел в стек
        node = node->left; // Переходим к левому потомку
    }
}

// Конструктор итератора постфиксного обхода
BinaryTree::PostOrderIterator::PostOrderIterator(TreeNode* root) : lastVisited(nullptr), current(root) 
{
    pushLeftMost(current); // Кладём в стек всю левую ветку начиная с корня
}

// Вспомогательный метод итератора для помещения в стек левой ветки начиная с node
void BinaryTree::PostOrderIterator::pushLeftMost(TreeNode* node) 
{
    postOrderPushLeftMost(s, node);
}

// Проверяет, есть ли ещё элементы для обхода в постфиксном порядке
bool BinaryTree::PostOrderIterator::hasNext() 
{
    return !s.empty(); // Возвращает true, если стек не пуст — значит есть ещё узлы для посещения
}

// Возвращает следующий элемент в постфиксном обходе
int BinaryTree::PostOrderIterator::next() 
{
    while (!s.empty()) 
    {
        TreeNode* peekNode = s.top();

        // Если правый потомок существует и мы его ещё не посетили
        if (peekNode->right && lastVisited != peekNode->right) 
        {
            pushLeftMost(peekNode->right); // переходим к нему (кладём в стек его левую ветку)
        }
        else  // Правый потомок отсутствует или уже посещён — можно обработать текущий узел
        {
            s.pop();
            lastVisited = peekNode; // Запоминаем последний посещённый узел
            return peekNode->value; // Возвращаем значение узла
        }
    }
    // Если стек пуст - обход завершён, дальнейших элементов нет
    throw out_of_range("Больше нет элементов");
}

// Создаёт и возвращает итератор для постфиксного обхода текущего дерева
BinaryTree::PostOrderIterator BinaryTree::getPostOrderIterator() const 
{
    return PostOrderIterator(root);
}