#include "Graf.h"

int main() 
{
    setlocale(LC_ALL, "ru");
    Graf g;

    cout << "Выберите способ построения матрицы смежности:\n";
    cout << "1. Из файла\n";
    cout << "2. С клавиатуры\n";
    cout << "3. Случайным образом\n";

    int choice = -1;
    while (choice < 1 || choice >3) 
    {
        choice = readInt("Введите число от 1 до 3: ");
        if (choice < 1 || choice >3)
            cout << "Некорректный выбор. Попробуйте снова.\n";
    }

    try 
    {
        switch (choice) 
        {
        case 1:
            g.buildFromFile("FileName1.txt");
            break;
        case 2:
            g.buildFromKeyboard();
            break;
        case 3:
            g.buildRandom();
            break;
        }

        g.printMatrix();
        int K1 = -1, K2 = -1;
        while (true) 
        {
            K1 = readInt("Введите номер города K1 (откуда летим): ");
            K2 = readInt("Введите номер города K2 (куда летим): ");
            int n = g.getN();
            if (K1 >= 1 && K1 <= n && K2 >= 1 && K2 <= n) 
            {
                break;
            }
            cout << "Номера городов должны быть в диапазоне от 1 до " << n << "\n";
        }

        g.findAllPaths(K1, K2);

        g.writePathsToFile("FileName2.txt");

        cout << "Поиск завершен. Результаты записаны в файл FileName2.txt\n";

    }
    catch (exception& e) 
    {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
