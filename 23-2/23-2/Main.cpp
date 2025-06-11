#include "Tree.h"

int main() 
{
    setlocale(LC_ALL, "ru");
    BinaryTree tree;

    cout << "Выберите способ заполнения дерева:\n";
    cout << "1. С клавиатуры\n2. Из файла\n3. Случайными числами\n";

    int choice; cin >> choice;

    switch (choice) 
    {
    case 1: 
    {
        cout << "Сколько чисел ввести? ";
        int n; cin >> n;
        tree.fillFromKeyboard(n);
        break;
    }
    case 2:
        tree.fillFromFile("a.txt");
        break;
    case 3: 
    {
        cout << "Сколько случайных чисел? ";
        int n; cin >> n;
        tree.fillRandom(n, 0, 100);
        break;
    }
    default:
        cout << "Неверный выбор\n";
        return 1;
    }

    cout << "\nПостроенное дерево:\n";
    tree.printTree();

    cout << "\nОбход дерева в порядке лево-право-корень:\n";

    auto it = tree.getPostOrderIterator();
    while (it.hasNext()) 
    {
        cout << it.next() << ' ';
    }
    cout << endl;

    return 0;
}
