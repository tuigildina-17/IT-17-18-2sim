#include "Tree.h"

int main()
{
    setlocale(LC_ALL, "ru");
    BinarySearchTree tree;
    vector<int> values;

    int choice;
    while (true)
    {
        cout << "Выберите способ заполнения дерева:\n";
        cout << "1. С клавиатуры\n2. Из файла\n3. Случайными числами\n";
        choice = readInt("Ваш выбор: ");
        if (choice >= 1 && choice <= 3)
            break;
        cout << "Некорректный выбор. Попробуйте ещё раз.\n";
    }

    if (choice == 1)
    {
        int n;
        while (true)
        {
            n = readInt("Сколько чисел хотите ввести? ");
            if (n > 0)
                break;
            cout << "Введите положительное число.\n";
        }
        cout << "Введите числа (через Enter):\n";
        int count = 0;
        while (count < n)
        {
            int val = readInt("");
            values.push_back(val);
            tree.insert(val);
            count++;
        }
    }
    else if (choice == 2)
    {
        ifstream fin("a.txt");
        if (!fin.is_open())
        {
            cout << "Не удалось открыть файл\n";
            return 1;
        }
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            int val;
            while (ss >> val)
            {
                values.push_back(val);
                tree.insert(val);
            }
        }
        fin.close();
        if (values.empty())
        {
            cout << "Файл пуст или содержит некорректные данные\n";
            return 1;
        }
    }
    else if (choice == 3)
    {
        int n;
        while (true)
        {
            n = readInt("Сколько случайных чисел создать? ");
            if (n > 0)
                break;
            cout << "Введите положительное число.\n";
        }
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < n; ++i)
        {
            int val = 1 + rand() % 100;
            values.push_back(val);
            tree.insert(val);
        }
    }

    printValues(values);

    cout << "Дерево:\n";
    tree.printTree();

    cout << "Обход дерева в порядке ЛКП: ";
    tree.inorder();
    cout << endl;

    // Преобразуем дерево в двусвязный список
    tree.flatten();
    // Печатаем двусвязный список
    tree.printList();

    return 0;
}