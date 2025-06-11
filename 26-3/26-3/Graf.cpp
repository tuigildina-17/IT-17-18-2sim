#include "Graf.h"

Graf::Graf() : n(0) 
{
}

void Graf::buildFromFile(const string& filename)
{
    ifstream fin(filename);
    if (!fin)
    {
        cerr << "Ошибка открытия файла " << filename << endl;
        n = 0;
        matrix.clear();
        return;
    }

    fin >> n;
    if (n <= 0 || n > 15)
    {
        cerr << "Неверное количество городов в файле (должно быть от 1 до 15 включительно)" << endl;
        n = 0;
        matrix.clear();
        return;
    }

    matrix.assign(n, vector<int>(n, 0));
    bool incorrectValue = false;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            fin >> matrix[i][j];
            if (matrix[i][j] < 0) matrix[i][j] = 0; // защита от отрицательных значений
            // Проверка, чтобы были только 1 или 0 в матрице
            if (matrix[i][j] != 0 && matrix[i][j] != 1)
            {
                cout << "Ошибка: в матрице найдены значения, отличные от 0 и 1. " << "Значение [" << i << "][" << j << "] = " << matrix[i][j] << " будет заменено на 0." << endl;
                matrix[i][j] = 0;
                incorrectValue = true;
            }

        }
    }

    fin.close();

    if (incorrectValue)
    {
        cout << "В файле были исправлены некорректные значения матрицы." << endl;
    }

    // Проверка и исправление симметрии
    bool symmetric = true;
    for (int i = 0; i < n && symmetric; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                symmetric = false;
                // Исправляем на максимум из двух значений
                int val = max(matrix[i][j], matrix[j][i]);
                matrix[i][j] = val;
                matrix[j][i] = val;
            }
        }
    }

    if (!symmetric)
    {
        cout << "Внимание: матрица смежности не была симметричной. Она была исправлена автоматически.\n";
    }
}

void Graf::buildFromKeyboard()
{
    while (true)
    {
        n = readInt("Введите количество городов (от 1 до 15 включительно): ");
        if (n > 0 && n <= 15) break;
        cout << "Количество городов должно быть от 1 до 15 включительно.\n";
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
    {
        int abjCount;
        while (true)
        {
            abjCount = readInt("Введите количество городов, в которые есть перелет из города " + to_string(i + 1) + ": ");
            if (abjCount >= 0 && abjCount <= n) break;
            cout << "Количество должно быть от 0 до " << n << ".\n";
        }

        set<int> adjSet; // чтобы не было повторов
        if (abjCount > 0)
            cout << "Введите номера городов, куда есть перелет из города " << (i + 1) << ": ";

        for (int k = 0; k < abjCount; ++k)
        {
            int v;
            while (true)
            {
                v = readInt("");
                if (v >= 1 && v <= n && adjSet.find(v) == adjSet.end() && v != i + 1) break;
                if (v == i + 1)
                    cout << "Пересадка в тот же город невозможна, введите другой город: ";
                else if (adjSet.find(v) != adjSet.end())
                    cout << "Город уже введен, введите другой: ";
                else
                    cout << "Неверный номер города, введите заново: ";
            }
            adjSet.insert(v);
            // Устанавливаем ребро в обе стороны — неориентированный граф
            matrix[i][v - 1] = 1;
            matrix[v - 1][i] = 1;
        }
    }
}

void Graf::buildRandom()
{
    while (true)
    {
        n = readInt("Введите количество городов (от 1 до 15 включительно): ");
        if (n > 0 && n <= 15) break;
        cout << "Количество городов должно быть от 1 до 15 включительно.\n";
    }

    matrix.assign(n, vector<int>(n, 0));

    srand(static_cast<unsigned int>(time(nullptr)));

    // Заполняем верхний треугольник матрицы случайными значениями 0 или 1
    for (int i = 0; i < n; ++i)
    {
        matrix[i][i] = 0; // петли запрещены
        for (int j = i + 1; j < n; ++j)
        {
            int val = rand() % 2; // случайно ставим ребро или нет
            matrix[i][j] = val;
            matrix[j][i] = val; // симметрично
        }
    }
}

// Вывод матрицы смежности
void Graf::printMatrix() const
{
    cout << "\nМатрица смежности (" << n << "x" << n << "):\n   ";
    for (int j = 0; j < n; ++j)
        cout << j + 1 << ' ';
    cout << '\n';

    // Проходим по каждой строке матрицы
    for (int i = 0; i < n; ++i)
    {
        cout.width(2);
        cout << i + 1 << ' ';
        // Выводим значения в строке — наличие ребра между городами
        for (int j = 0; j < n; ++j) 
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

// Поиск всех путей из start в end
void Graf::findPaths(int current, int dest, vector<int>& path, vector<bool>& visited) 
{
    visited[current] = true; // Отмечаем текущий узел как посещённый
    path.push_back(current + 1); // Добавляем текущий город в путь (+1 для вывода с 1)

    if (current == dest) 
    {
        allPaths.push_back(path); // Если достигли конечного города — сохраняем путь
    }
    else 
    {
        // Перебираем соседей в порядке возрастания для лексикографического порядка
        for (int next = 0; next < n; ++next) 
        {
            // Если есть ребро и город ещё не посещён — рекурсивно идём дальше
            if (matrix[current][next] == 1 && !visited[next]) 
            {
                findPaths(next, dest, path, visited);
            }
        }
    }

    path.pop_back(); // Убираем текущий город из пути при возврате из рекурсии
    visited[current] = false; // Отмечаем город как непосещённый для других путей
}

// Вспомогательная функция для поиска всех путей между двумя городами
void Graf::findAllPaths(int start, int end) 
{
    allPaths.clear(); // Очищаем список всех найденных путей
    vector<int> path; // Текущий путь
    vector<bool> visited(n, false); // Посещённые вершины

    findPaths(start - 1, end - 1, path, visited);

    // Сортируем сначала по длине маршрута, потом лексикографически
    sort(allPaths.begin(), allPaths.end(), [](const vector<int>& a, const vector<int>& b) 
        {
        if (a.size() != b.size())
            return a.size() < b.size();
        return a < b;
        });
}

// Запись всех найденных путей в файл
void Graf::writePathsToFile(const string& filename) const 
{
    ofstream fout(filename);
    if (!fout) 
    {
        cerr << "Ошибка открытия файла для записи\n";
        return;
    }

    if (allPaths.empty()) 
    {
        fout << -1 << '\n'; // Если путей нет — выводим -1
        return;
    }

    fout << allPaths.size() << '\n'; // Количество найденных путей
    for (const auto& path : allPaths) 
    {
        for (size_t i = 0; i < path.size(); ++i) 
        {
            fout << path[i];
            if (i + 1 != path.size())
                fout << ' ';
        }
        fout << '\n';
    }
}

// Функция для чтения целого числа с проверкой ввода
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
