#include "Tree.h"

BinaryTree::BinaryTree() : root(nullptr), overlapCount(0) 
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
        else {
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

void BinaryTree::printTree(TreeNode* node, int space) const
{
    if (!node) return;
    const int indent = 5;
    space += indent;

    printTree(node->right, space);

    cout << endl;
    for (int i = indent; i < space; i++) cout << ' ';
    cout << node->value << "\n";

    printTree(node->left, space);
}

void BinaryTree::printTree() const
{
    if (!root)
    {
        cout << "Дерево пустое\n";
        return;
    }
    printTree(root, 0);
}

void BinaryTree::fillFromKeyboard()
{
    cout << "Введите количество элементов: ";
    int n; cin >> n;
    cout << "Введите элементы:\n";
    for (int i = 0; i < n; ++i)
    {
        int v; cin >> v;
        insert(v);
    }
}

bool BinaryTree::fillFromFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin.is_open()) return false;

    int v;
    while (fin >> v)
        insert(v);

    fin.close();
    return true;
}

void BinaryTree::fillRandom(int n, int minVal, int maxVal)
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < n; ++i)
    {
        int val = minVal + rand() % (maxVal - minVal + 1);
        insert(val);
    }
}

// 0 - не покрыт
// 1 - покрыт
// 2 - камера на этом узле

int BinaryTree::cameraPositions(TreeNode* node)
{
    if (!node) return 1; // Пустой узел считается покрытым

    int left = cameraPositions(node->left); // Рекурсивно получить статус левого ребенка
    int right = cameraPositions(node->right); // Рекурсивно получить статус правого ребенка

    // Если хотя бы один ребенок не покрыт, ставим камеру в текущем узле
    if (left == 0 || right == 0)
    {
        cameraNodes.push_back(node);
        return 2; // Камера на этом узле
    }

    // Если хотя бы один ребенок имеет камеру, текущий узел покрыт
    if (left == 2 || right == 2)
        return 1; // Узел покрыт

    return 0; // Иначе узел не покрыт
}

// Подсчитывает количество узлов, покрытых более чем одной камерой, и сохраняет их в overlappedNodes
void BinaryTree::countCoverage(TreeNode* node)
{
    if (!node) return;

    overlappedNodes.clear(); // Очистить список узлов с перекрытием покрытия

    map<TreeNode*, int> coverageMap; // Счётчик покрытия для каждого узла

    set<TreeNode*> camerasSet(cameraNodes.begin(), cameraNodes.end()); // Множество узлов с камерами

    // Обход дерева для подсчёта покрытия каждого узла
    function<void(TreeNode*, TreeNode*)> coverage = [&](TreeNode* cur, TreeNode* parent)
        {
            if (!cur) return;

            // Если у текущего есть камера - увеличить счетчик покрытия для него и соседей
            if (camerasSet.count(cur))
            {
                coverageMap[cur]++;
                if (parent) coverageMap[parent]++;
                if (cur->left) coverageMap[cur->left]++;
                if (cur->right) coverageMap[cur->right]++;
            }

            coverage(cur->left, cur);
            coverage(cur->right, cur);
        };

    coverage(root, nullptr);

    overlapCount = 0;

    // Обход дерева для поиска узлов, покрытых более чем одной камерой
    function<void(TreeNode*)> countOverlap = [&](TreeNode* cur)
        {
            if (!cur) return;
            if (coverageMap[cur] > 1) {
                overlapCount++;
                overlappedNodes.push_back(cur);
            }
            countOverlap(cur->left);
            countOverlap(cur->right);
        };

    countOverlap(root);
}

// Функция для установки камер в дереве
void BinaryTree::placeCameras()
{
    cameraNodes.clear();

    int rootState = cameraPositions(root);

    // Если корень не покрыт, установить камеру на корне
    if (rootState == 0)
        cameraNodes.push_back(root);

    countCoverage(root);
}

// Выводит список узлов, которые покрыты более чем одной камерой
void BinaryTree::printOverlappedNodes() const 
{
    if (overlappedNodes.empty()) 
    {
        cout << "Нет узлов, покрытых более чем одной камерой.\n";
        return;
    }
    cout << "Узлы, покрытые более чем одной камерой: ";
    for (auto node : overlappedNodes) 
    {
        cout << node->value << " ";
    }
    cout << endl;
}