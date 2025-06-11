//Юный путешественник решил изучить схему авиационного сообщения Схема
//авиационного сообщения задана в текстовом файле с именем FileName1.в виде матрицы
//смежности.Первая строка файла содержит количество городов(n) n <= 15, связанных
//авиационным сообщением, а следующие n строк хранят матрицу(m), m[i][j] = 0, если не
//имеется возможности перелета из города i в город j, иначе m[i][j] = 1. Определить все
//маршруты перелета из города К1 в город К2 В файл с именем FileName2 в первой строке
//выведите число таких маршрутов, а в следующих строках перечислите все такие маршруты
//в порядке от самых коротких к более длинным, маршруты одинаковой длины перечисляйте
//в лексикографическом порядке.Маршрут задается перечислением номеров городов,
//нумерация городов идет с 1. Если таких маршрутов нет, выведите число(-1).

#ifndef GRAF_H
#define GRAF_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <random>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

class Graf 
{
private:
    int n; // количество городов
    vector<vector<int>> matrix; // матрица смежности
    vector<vector<int>> allPaths; // все найденные маршруты

    /*bool isSymmetric() const;
    bool noLoops() const;
    bool validateMatrix() const;*/

    void findPaths(int current, int dest, vector<int>& path, vector<bool>& visited);

public:
    Graf();

    void buildFromFile(const string& filename);
    void buildFromKeyboard();
    void buildRandom();

    void printMatrix() const;

    void findAllPaths(int start, int end);

    void writePathsToFile(const string& filename) const;

    int getN() const 
    {
        return n; 
    }
};

int readInt(const string& prompt);

#endif
