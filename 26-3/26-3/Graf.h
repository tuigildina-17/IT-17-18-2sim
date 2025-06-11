//���� �������������� ����� ������� ����� ������������ ��������� �����
//������������ ��������� ������ � ��������� ����� � ������ FileName1.� ���� �������
//���������.������ ������ ����� �������� ���������� �������(n) n <= 15, ���������
//����������� ����������, � ��������� n ����� ������ �������(m), m[i][j] = 0, ���� ��
//������� ����������� �������� �� ������ i � ����� j, ����� m[i][j] = 1. ���������� ���
//�������� �������� �� ������ �1 � ����� �2 � ���� � ������ FileName2 � ������ ������
//�������� ����� ����� ���������, � � ��������� ������� ����������� ��� ����� ��������
//� ������� �� ����� �������� � ����� �������, �������� ���������� ����� ������������
//� ������������������ �������.������� �������� ������������� ������� �������,
//��������� ������� ���� � 1. ���� ����� ��������� ���, �������� �����(-1).

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
    int n; // ���������� �������
    vector<vector<int>> matrix; // ������� ���������
    vector<vector<int>> allPaths; // ��� ��������� ��������

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
