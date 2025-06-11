#include "Tree.h"

// Конструктор класса BinaryTree (инициализирует корень дерева значением nullptr (пустое дерево))
BinaryTree::BinaryTree() : root(nullptr)
{
}

// Деструктор класса BinaryTree (удаляет все узлы дерева, начиная с корня)
BinaryTree::~BinaryTree()
{
    deleteTree(root);
}

// Рекурсивный метод для удаления узлов дерева (удаляет узел и все его поддеревья)
void BinaryTree::deleteTree(TreeNode* node)
{
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}


// Метод для вставки значения в дерево
void BinaryTree::insert(int value)
{
    if (!root) 
    {
        root = new TreeNode(value);
        return;
    }

    // Используем очередь для поиска первого доступного места
    queue<TreeNode*> q;
    q.push(root); // Начинаем с корня

    while (!q.empty()) 
    {
        TreeNode* current = q.front(); // Берем узел из начала очереди
        q.pop(); // Удаляем дерево из очереди

        // Проверяем левое поддерево
        if (!current->left) 
        {
            current->left = new TreeNode(value);
            return;
        }
        else {
            q.push(current->left);
        }

        // Проверяем правое поддерево
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

// Рекурсивный метод для печати дерева
void BinaryTree::printTree(TreeNode* node, int space) const
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
void BinaryTree::printTree() const
{
    if (!root)
    {
        cout << "Дерево пустое\n";
        return;
    }
    printTree(root, 0); // Вызываем рекурсивный метод печати с корнем дерева
}

// Метод для проверки, является ли дерево идеально сбалансированным
bool BinaryTree::isBalanced() const
{
    int height = 0; // Переменная для высоты
    return isBalanced(root, height); // // Вызов вспомогательного метода с корнем дерева
}

// Вспомогательный метод для проверки сбалансированности дерева
bool BinaryTree::isBalanced(TreeNode* node, int& height) const
{
    if (!node)
    {
        height = 0; // Для пустого узла высота 0
        return true; // Пустое дерево сбалансировано
    }

    // Переменные для хранения высот левого и правого поддеревьев
    int leftHeight = 0, rightHeight = 0;

    // Рекурсивно проверяем левое и правое поддеревья
    bool leftBalanced = isBalanced(node->left, leftHeight);
    bool rightBalanced = isBalanced(node->right, rightHeight);

    // Высота текущего узла равна максимальной высоте его поддеревьев плюс 1 (для самого узла)
    height = max(leftHeight, rightHeight) + 1;

    // Возвращаем true, если оба поддерева сбалансированы и разница их высот не превышает 1
    return leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1;
}

// Метод для заполнения дерева значениями, введенными пользователем с клавиатуры
void BinaryTree::fillFromKeyboard(int count)
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

// Метод для заполнения дерева случайными значениями
void BinaryTree::fillRandom(int count, int min, int max)
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