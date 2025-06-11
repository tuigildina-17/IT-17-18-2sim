//���� �������������� ����� ������� ����� ������������ ��������� �����
//������������ ��������� ������ � ��������� ����� � ������ FileName.� ���� �������
//���������.������ ������ ����� �������� ���������� �������(n) n <= 25, ���������
//����������� ����������, � ��������� n ����� ������ �������(m), m[i][j] = 0, ���� ��
//������� ����������� �������� �� ������ i � ����� j, ����� m[i][j] = 1. ���������� ������
//�������, � ������� �� ������ K ����� �������� ����� � L ����������� ��� ������
//��������� ����.����������� ������ ����� ������� � ������� �����������.���������
//������� ���������� � 1. ���� ����� ������� ���, �������� �����(-1).

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
    int n; // ���������� �������
    vector<vector<int>> matrix; // ������� ���������

public:
    Graf();

    void buildFromFile(const string& filename);
    void buildFromKeyboard();
    void buildRandom();

    void printMatrix() const;

    // ���������� ������ �������, ���������� �� K ����� � L ����������� (�� ����������� ����)
    vector<int> citiesWithLStops(int K, int L) const;

    int getN() const 
    { 
        return n; 
    }
};

int readInt(const string& prompt);

#endif
