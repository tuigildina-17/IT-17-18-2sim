#include "Tree.h"

int main()
{
    setlocale(LC_ALL, "ru");
    BinaryTree tree;

    cout << "Выберите способ заполнения дерева:\n";
    cout << "1. С клавиатуры\n";
    cout << "2. Из файла\n";
    cout << "3. Случайными числами\n";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        tree.fillFromKeyboard();
        break;
    case 2:
        if (!tree.fillFromFile("a.txt"))
            cout << "Ошибка при открытии файла\n";
        break;
    case 3:
    {
        int n;
        cout << "Введите количество случайных элементов: ";
        cin >> n;
        tree.fillRandom(n, 0, 100);
    }
    break;
    default:
        cout << "Неверный выбор\n";
        return 1;
    }

    cout << "\nПостроенное дерево:\n";
    tree.printTree();


    tree.placeCameras();


    cout << "Узлы с камерами: ";
    for (auto node : tree.getCameraNodes())
        cout << node->value << " ";

    cout << "\nКоличество узлов, покрытых более чем одной камерой: " << tree.getOverlapCount() << "\n";

    tree.countCoverage(tree.getRoot());

    tree.printOverlappedNodes();

    return 0;
}
