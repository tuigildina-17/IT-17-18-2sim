#include "Graf.h"

int main() 
{
    setlocale(LC_ALL, "ru");
    Graf g;

    cout << "Выберите способ построения матрицы смежности:\n" << "1. Из файла\n" << "2. С клавиатуры\n" << "3. Случайным образом\n";

    int choice;
    while (true) 
    {
        choice = readInt("Ваш выбор: ");
        if (choice >= 1 && choice <= 3) break;
        cout << "Введите число от 1 до 3.\n";
    }

    switch (choice) 
    {
    case 1:
        g.buildFromFile("a.txt");
        if (g.getN() == 0) 
        {
            cout << "Не удалось построить граф из файла.\n";
            return 1;
        }
        break;
    case 2:
        g.buildFromKeyboard();
        break;
    case 3:
        g.buildRandom();
        break;
    }

    g.printMatrix();

    int K, L;

    while (true) 
    {
        K = readInt("\nВведите номер города отправления K: ");
        if (K >= 1 && K <= g.getN()) break;
        cout << "Номер города должен быть от 1 до " << g.getN() << ".\n";
    }

    while (true) 
    {
        L = readInt("Введите количество пересадок L: ");
        if (L >= 0) break;
        cout << "Количество пересадок не может быть отрицательным.\n";
    }

    vector<int> reachable = g.citiesWithLStops(K, L);

    if (reachable.empty()) 
    {
        cout << "-1\n";
    }
    else 
    {
        sort(reachable.begin(), reachable.end());
        cout << "\nГорода, достижимые из города " << K << " ровно с " << L << " пересадками:\n";
        for (int city : reachable)
            cout << city << ' ';
        cout << '\n';
    }

    return 0;
}
