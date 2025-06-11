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
    if (n <= 0 || n > 25) 
    {
        cerr << "Неверное количество городов в файле (должно быть от 1 до 25 включительно)" << endl;
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
        n = readInt("Введите количество городов (от 1 до 25 включительно): ");
        if (n > 0 && n <= 25) break;
        cout << "Количество городов должно быть от 1 до 25 включительно.\n";
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
            /*matrix[i][v - 1] = 1;*/
        }
    }
}

void Graf::buildRandom() 
{
    while (true) 
    {
        n = readInt("Введите количество городов (от 1 до 25 включительно): ");
        if (n > 0 && n <= 25) break;
        cout << "Количество городов должно быть от 1 до 25 включительно.\n";
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
    //for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        if (i == j)
    //            matrix[i][j] = 0; // петли не ставим
    //        else
    //            matrix[i][j] = rand() % 2;
    //    }
    //}
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

// Поиск городов, достижимых из K ровно с L пересадками по кратчайшему пути
vector<int> Graf::citiesWithLStops(int K, int L) const 
{
    // K - номер города, откуда стартуем (1..n)
    // L - количество пересадок

    vector<int> dist(n, -1); // расстояния в ребрах от K-1
    queue<int> q;

    dist[K - 1] = 0; // расстояние до стартового города равно 0
    q.push(K - 1); // помещаем стартовый город в очередь для обхода

    // Выполняем обход для поиска кратчайших путей
    while (!q.empty()) 
    {
        int u = q.front(); 
        q.pop();

        // Рассматриваем всех соседей города u
        for (int v = 0; v < n; ++v) 
        {
            // Если есть ребро из u в v и город v еще не посещен
            if (matrix[u][v] == 1 && dist[v] == -1) 
            {
                dist[v] = dist[u] + 1; // обновляем расстояние до v
                q.push(v); // добавляем v в очередь для дальнейшего обхода
            }
        }
    }

    vector<int> result;
    for (int i = 0; i < n; ++i) 
    {
        if (dist[i] == L)
            result.push_back(i + 1);
    }

    return result;
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
