//ёный путешественник решил изучить схему авиационного сообщени€ —хема
//авиационного сообщени€ задана в текстовом файле с именем FileName.в виде матрицы
//смежности.ѕерва€ строка файла содержит количество городов(n) n <= 25, св€занных
//авиационным сообщением, а следующие n строк хран€т матрицу(m), m[i][j] = 0, если не
//имеетс€ возможности перелета из города i в город j, иначе m[i][j] = 1. ќпределить номера
//городов, в которые из города K можно долететь ровно с L пересадками дл€ самого
//короткого пути.ѕеречислите номера таких городов в пор€дке возрастани€.Ќумераци€
//городов начинаетс€ с 1. ≈сли таких городов нет, выведите число(-1).

#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Graf 
{
private:
    int n; // количество городов
    vector<vector<int>> matrix; // матрица смежности

public:
    Graf();

    void buildFromFile(const string& filename);
    void buildFromKeyboard();
    void buildRandom();

    void printMatrix() const;

    // ¬озвращает вектор городов, достижимых из K ровно с L пересадками (по кратчайшему пути)
    vector<int> citiesWithLStops(int K, int L) const;

    int getN() const 
    { 
        return n; 
    }
};

int readInt(const string& prompt);

#endif
