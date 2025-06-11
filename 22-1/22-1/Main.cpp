#include "Tree.h"

int main()
{
    setlocale(LC_ALL, "ru");
    ifstream file("filename.txt");

    vector<string> tokens;
    int choice;

    cout << "Выберите способ ввода: 1. Из файла 2. С клавиатуры\n";
    cin >> choice;

    if (choice == 1) {
        ifstream file("filename.txt");
        string token;

        // Читаем элементы из файла и добавляем их в вектор
        while (file >> token)
        {
            tokens.push_back(token);
        }
        file.close();
    }
    else if (choice == 2)
    {
        string token;
        cout << "Введите выражение (в конце напишите end):\n";

        while (cin >> token && token != "end")
        {
            tokens.push_back(token);
        }
    }
    else
    {
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    PrintTokens(tokens); // Выводим все элементы на экран

    // Проверяем корректность выражения
    if (!CorrectExpression(tokens))
    {
        cout << "Выражение некорректно." << endl;
        return 1;
    }

    // Строим дерево выражений
    PNode rootNode = BuildTree(tokens);

    cout << "Дерево выражений:" << endl;
    PrintTree(rootNode, 0); // Выводим дерево выражений на экран

    // Преобразуем дерево выражений
    rootNode = TransformTree(rootNode);

    cout << "Преобразованное дерево выражений:" << endl;
    PrintTree(rootNode, 0); // Выводим преобразованное дерево на экран

    // Выводим адрес корня дерева
    cout << "Адрес корня преобразованного дерева: " << static_cast<void*>(rootNode) << endl;

    int result = EvaluateTree(rootNode); // Выводим результат вычисления
    cout << "Результат выражения: " << result << endl;

    return 0;
}
