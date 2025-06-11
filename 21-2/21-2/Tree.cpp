#include "Tree.h"

// Конструктор класса BinarySearchTree (инициализирует корень дерева значением nullptr (пустое дерево))
BinarySearchTree::BinarySearchTree() : root(nullptr)
{
}

// Деструктор класса BinarySearchTree (удаляет все узлы дерева, начиная с корня)
BinarySearchTree::~BinarySearchTree()
{
    deleteTree(root);
}

// Рекурсивный метод для удаления узлов дерева (удаляет узел и все его поддеревья)
void BinarySearchTree::deleteTree(TreeNode* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// Рекурсивный метод для вставки значения в дерево (вставляет значение в правильную позицию в поддереве)
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

// Метод для вставки значения в дерево с использованием корня
void BinarySearchTree::insert(int value)
{
    insert(root, value);
}

// Рекурсивный метод для печати дерева
void BinarySearchTree::printTree(TreeNode* node, int space) const
{
    if (!node) return;
    const int indent = 5; // Уровень отступа
    space += indent;

    printTree(node->right, space); // Печатаем правое поддерево

    cout << endl;
    for (int i = indent; i < space; i++) cout << ' '; // Отступы
    cout << node->value << "\n"; // Печатаем текущее значение

    printTree(node->left, space); // Печатаем левое поддерево
}

// Метод для печати всего дерева с использованием корня
void BinarySearchTree::printTree() const
{
    if (!root)
    {
        cout << "Дерево пустое\n";
        return;
    }
    printTree(root, 0); // Вызываем рекурсивный метод печати с корнем дерева
}

// Метод для заполнения дерева значениями, введенными пользователем с клавиатуры
void BinarySearchTree::fillFromKeyboard(int count)
{
    cout << "Введите " << count << " целых чисел через Enter:\n";
    for (int i = 0; i < count; ++i)
    {
        int val;
        cin >> val;
        insert(val);
    }
}

// Метод для заполнения дерева значениями из файла
void BinarySearchTree::fillFromFile(const string& filename)
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

// Метод для заполнения дерева случайными значениями
void BinarySearchTree::fillRandom(int count, int min, int max)
{
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < count; ++i)
    {
        int val = min + rand() % (max - min + 1);
        insert(val);
    }
}

// Функция для вывода значений на экран
void printValues(const vector<int>& values)
{
    cout << "Исходные числа:\n";
    for (int v : values)
    {
        cout << v << " ";
    }
    cout << "\n";
}

// Функция для чтения целого числа
int readInt(const string& prompt)
{
    int val;
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cout << "Ошибка ввода. Повторите.\n";
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
        cout << "Неверный ввод. Введите целое число без лишних символов.\n";
    }
}
