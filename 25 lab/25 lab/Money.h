//1. �������������� �����, ������������ ��������� �������� �������������.�����������
//����������� ������(����, ��������, ������������(�� ����� ����), ���������� ���������
//    ������ ��� ������ �����, �������� ����� �������� ��������).�������������� ��� ������,
//    ������� ������������(�� ��������� ��������� �������� ������������� ������
//        �� ������������).
//    Money 
//    unsigned int rubles
//    short int kopeks
//    ��������� ���� �������� ����
//    Money.��������� ������ ���� ����
//    bool.
//2. �������� � �������������� � ������ ������� ������ ��������� � �������� �������������
//��������.�������������� ��� ��������
//������� �������� :
//--��������� ������� �� ������� ���� Money
//++ ���������� ������� � ������� ���� Money
//�������� ���������� ���� :
//unsigned int(�������) ����������� �������� ����������
//������(������� �������������);
//double(�����) ����������� �������� �������, ������������ �
//�����, ����� ����� �������������, ��������� < 1.
//    �������� �������� :
//-Money m � ��������� ����
//- ����� ����� � ��������� ������ �� �������� �����

#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <cctype>
#include <limits>
#include <string>

using namespace std;

class Money 
{
private:
    unsigned int rubles;
    short int kopeks; // 0..99

    void normalize(); // ���������� � ����������� ���� (��������, ���� kopeks >= 100)

public:
    // ������������
    Money(); // �� ��������� - 0 ������ 0 ������
    Money(unsigned int r); // �����, ������� = 0
    Money(unsigned int r, short int k); // ����� � �������
    Money(const Money& other); // �����������
    static Money createCopy(const Money& other);

    // �������
    unsigned int getRubles() const;
    short int getKopeks() const;

    // ������� � ��������� ������������
    void setRubles(unsigned int r);
    bool setKopeks(short int k); // ���������� false, ���� �����������

    // ����� ��������� ���� �������� Money
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // ���������� ��������� ������
    friend ostream& operator<<(ostream& os, const Money& m);


    // ��������� ��� 2 �������

    // ������� ++ (�������)
    Money& operator++();

    // ������� ++ (��������)
    Money operator++(int);

    // ������� -- (�������)
    Money& operator--();

    // ������� -- (��������)
    Money operator--(int);

    // �������� ���������� �����
    operator unsigned int() const;   // ������� ���������� � ������ (��� ������)
    explicit operator double() const; // ����� ���������� � ������� ������

    // �������� �������� ���������
    Money operator-(const Money& other) const;
    Money operator-(int kopeks) const;

    // ������� ��� �������� � �����
    static bool isValidUnsignedInt(const string& s);
    static unsigned int inputUnsignedInt(const string& prompt);

    static bool isValidShortInt(const string& s);
    static short int inputShortInt(const string& prompt);
};

#endif
