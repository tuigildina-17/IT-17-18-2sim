#include "Graf.h"

Graf::Graf() : n(0) 
{
}

void Graf::buildFromFile(const string& filename) 
{
    ifstream fin(filename);
    if (!fin) 
    {
        cerr << "������ �������� ����� " << filename << endl;
        n = 0;
        matrix.clear();
        return;
    }

    fin >> n;
    if (n <= 0 || n > 25) 
    {
        cerr << "�������� ���������� ������� � ����� (������ ���� �� 1 �� 25 ������������)" << endl;
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
            if (matrix[i][j] < 0) matrix[i][j] = 0; // ������ �� ������������� ��������
            // ��������, ����� ���� ������ 1 ��� 0 � �������
            if (matrix[i][j] != 0 && matrix[i][j] != 1)
            {
                cout << "������: � ������� ������� ��������, �������� �� 0 � 1. " << "�������� [" << i << "][" << j << "] = " << matrix[i][j] << " ����� �������� �� 0." << endl;
                matrix[i][j] = 0;
                incorrectValue = true;
            }

        }
    }

    fin.close();

    if (incorrectValue)
    {
        cout << "� ����� ���� ���������� ������������ �������� �������." << endl;
    }

    // �������� � ����������� ���������
    bool symmetric = true;
    for (int i = 0; i < n && symmetric; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                symmetric = false;
                // ���������� �� �������� �� ���� ��������
                int val = max(matrix[i][j], matrix[j][i]);
                matrix[i][j] = val;
                matrix[j][i] = val;
            }
        }
    }

    if (!symmetric)
    {
        cout << "��������: ������� ��������� �� ���� ������������. ��� ���� ���������� �������������.\n";
    }
}

void Graf::buildFromKeyboard() 
{
    while (true) 
    {
        n = readInt("������� ���������� ������� (�� 1 �� 25 ������������): ");
        if (n > 0 && n <= 25) break;
        cout << "���������� ������� ������ ���� �� 1 �� 25 ������������.\n";
    }

    matrix.assign(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) 
    {
        int abjCount;
        while (true) 
        {
            abjCount = readInt("������� ���������� �������, � ������� ���� ������� �� ������ " + to_string(i + 1) + ": ");
            if (abjCount >= 0 && abjCount <= n) break;
            cout << "���������� ������ ���� �� 0 �� " << n << ".\n";
        }

        set<int> adjSet; // ����� �� ���� ��������
        if (abjCount > 0)
            cout << "������� ������ �������, ���� ���� ������� �� ������ " << (i + 1) << ": ";

        for (int k = 0; k < abjCount; ++k) 
        {
            int v;
            while (true) 
            {
                v = readInt("");
                if (v >= 1 && v <= n && adjSet.find(v) == adjSet.end() && v != i + 1) break;
                if (v == i + 1)
                    cout << "��������� � ��� �� ����� ����������, ������� ������ �����: ";
                else if (adjSet.find(v) != adjSet.end())
                    cout << "����� ��� ������, ������� ������: ";
                else
                    cout << "�������� ����� ������, ������� ������: ";
            }
            adjSet.insert(v);
            // ������������� ����� � ��� ������� � ����������������� ����
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
        n = readInt("������� ���������� ������� (�� 1 �� 25 ������������): ");
        if (n > 0 && n <= 25) break;
        cout << "���������� ������� ������ ���� �� 1 �� 25 ������������.\n";
    }

    matrix.assign(n, vector<int>(n, 0));
    srand(static_cast<unsigned int>(time(nullptr)));

    // ��������� ������� ����������� ������� ���������� ���������� 0 ��� 1
    for (int i = 0; i < n; ++i) 
    {
        matrix[i][i] = 0; // ����� ���������
        for (int j = i + 1; j < n; ++j) 
        {
            int val = rand() % 2; // �������� ������ ����� ��� ���
            matrix[i][j] = val;
            matrix[j][i] = val; // �����������
        }
    }
    //for (int i = 0; i < n; ++i) {
    //    for (int j = 0; j < n; ++j) {
    //        if (i == j)
    //            matrix[i][j] = 0; // ����� �� ������
    //        else
    //            matrix[i][j] = rand() % 2;
    //    }
    //}
}

// ����� ������� ���������
void Graf::printMatrix() const 
{
    cout << "\n������� ��������� (" << n << "x" << n << "):\n   ";
    for (int j = 0; j < n; ++j)
        cout << j + 1 << ' ';
    cout << '\n';

    // �������� �� ������ ������ �������
    for (int i = 0; i < n; ++i) 
    {
        cout.width(2);
        cout << i + 1 << ' ';
        // ������� �������� � ������ � ������� ����� ����� ��������
        for (int j = 0; j < n; ++j) 
        {
            cout << matrix[i][j] << ' ';
        }
        cout << '\n';
    }
}

// ����� �������, ���������� �� K ����� � L ����������� �� ����������� ����
vector<int> Graf::citiesWithLStops(int K, int L) const 
{
    // K - ����� ������, ������ �������� (1..n)
    // L - ���������� ���������

    vector<int> dist(n, -1); // ���������� � ������ �� K-1
    queue<int> q;

    dist[K - 1] = 0; // ���������� �� ���������� ������ ����� 0
    q.push(K - 1); // �������� ��������� ����� � ������� ��� ������

    // ��������� ����� ��� ������ ���������� �����
    while (!q.empty()) 
    {
        int u = q.front(); 
        q.pop();

        // ������������� ���� ������� ������ u
        for (int v = 0; v < n; ++v) 
        {
            // ���� ���� ����� �� u � v � ����� v ��� �� �������
            if (matrix[u][v] == 1 && dist[v] == -1) 
            {
                dist[v] = dist[u] + 1; // ��������� ���������� �� v
                q.push(v); // ��������� v � ������� ��� ����������� ������
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

// ������� ��� ������ ������ ����� � ��������� �����
int readInt(const string& prompt)
{
    int val;
    string line;
    while (true)
    {
        cout << prompt;
        if (!getline(cin, line))
        {
            cout << "������ �����. ���������.\n";
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
        cout << "�������� ����. ������� ����� ����� ��� ������ ��������.\n";
    }
}
