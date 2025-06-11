#include "Money.h"

// ������������: ���� kopeks >= 100, ��������� ������ ������� � �����
void Money::normalize() 
{
    if (kopeks < 0) 
    {
        // ���� ������������� �������� ������, ������������� � 0 (������ �� ������������ ������)
        kopeks = 0;
    }
    if (kopeks >= 100) 
    {
        rubles += kopeks / 100; // ��������� ������ ����� ������ � 1 �����
        kopeks = kopeks % 100; // ���������� ������� ����� �������� � �����
    }
}


// ������������

// ����������� �� ���������: ����� 0 ���. 0 ���.
Money::Money() : rubles(0), kopeks(0) 
{
}

// ����������� � ��������� ������ ������, ������� �� ��������� 0
Money::Money(unsigned int r) : rubles(r), kopeks(0) 
{
}

// ����������� � ��������� ������ � ������, � ������� ������������
Money::Money(unsigned int r, short int k) : rubles(r), kopeks(k) 
{
    normalize(); // ������������ ���������� ��������� �������
}

// ����������� �����������
Money::Money(const Money& other) : rubles(other.rubles), kopeks(other.kopeks)
{
}

Money Money::createCopy(const Money& other) 
{
    return Money(other);
}

// ������� - ������ ��� ��������� �������� �����

unsigned int Money::getRubles() const 
{
    return rubles; // ���������� ���������� ������
}

short int Money::getKopeks() const 
{
    return kopeks; // ���������� ���������� ������
}


// ������� � ������ ��� ��������� �������� �����

void Money::setRubles(unsigned int r) 
{
    rubles = r; // ������������� �������� ������ ��� �����������
}

bool Money::setKopeks(short int k) 
{
    // ��������� ������������ �������� ������: ������ ���� �� 0 �� 99 ������������
    if (k < 0 || k >= 100) 
    {
        return false; // ������������ ��������
    }
    kopeks = k; // ������������� �������� ������
    return true; // �������
}


// ��������� ���������

// �������� ��������� ���� �������� Money (����� � ������� ������ ���������)
bool Money::operator==(const Money& other) const 
{
    return (rubles == other.rubles) && (kopeks == other.kopeks);
}

// �������� ����������� 
bool Money::operator!=(const Money& other) const 
{
    return !(*this == other);
}


// ���������� ��������� ������
ostream& operator<<(ostream& os, const Money& m) 
{
    os << m.rubles << " ���. " << m.kopeks << " ���.";
    return os;
}


// ��������� ��� 2 �������

// ������� ++ (��������� 1 �������)
Money& Money::operator++()
{
    kopeks++;
    normalize();
    return *this;
}

// �������� ++ (��������� 1 �������, ���������� ������ ��������)
Money Money::operator++(int)
{
    Money temp = *this;
    ++(*this);
    return temp;
}

// ������� -- (�������� 1 �������)
Money& Money::operator--()
{
    if (kopeks == 0)
    {
        if (rubles > 0)
        {
            rubles--;
            kopeks = 99;
        }
        else
        {
            // ��� 0 ������ � 0 ������ - ������ �� ������
            kopeks = 0;
        }
    }
    else
        kopeks--;
    return *this;
}

// �������� -- (�������� 1 �������, ���������� ������ ��������)
Money Money::operator--(int)
{
    Money temp = *this;
    --(*this);
    return temp;
}

// ������� ���������� � unsigned int � ���������� ������ ��� ������
Money::operator unsigned int() const
{
    return rubles;
}

// ����� ���������� � double � ����� + ������� ����� �� ������
Money::operator double() const
{
    return rubles + kopeks / 100.0;
}

// ��������� ���� ����
Money Money::operator-(const Money& other) const
{
    int totalKopeks1 = static_cast<int>(rubles) * 100 + kopeks;
    int totalKopeks2 = static_cast<int>(other.rubles) * 100 + other.kopeks;
    int diff = totalKopeks1 - totalKopeks2;

    if (diff < 0) diff = 0;

    unsigned int newRubles = diff / 100;
    short int newKopeks = diff % 100;

    return Money(newRubles, newKopeks);
}

// ��������� ������ �� �����
Money Money::operator-(int k) const
{
    int totalKopeks = static_cast<int>(rubles) * 100 + kopeks;
    int diff = totalKopeks - k;

    if (diff < 0) diff = 0;

    unsigned int newRubles = diff / 100;
    short int newKopeks = diff % 100;

    return Money(newRubles, newKopeks);
}


// ��������, ��� ������ � ��������������� ����� ����� (��� ������ ��������)
bool Money::isValidUnsignedInt(const string& s)
{
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

// ���� unsigned int � ��������� � �������� ������� ��� ������
unsigned int Money::inputUnsignedInt(const string & prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        getline(cin, line);

        if (isValidUnsignedInt(line))
        {
            try {
                unsigned long val = std::stoul(line);
                if (val <= std::numeric_limits<unsigned int>::max())
                    return static_cast<unsigned int>(val);
            }
            catch (...) {}
        }
        cout << "������: ������� ��������������� ����� ����� ��� ������ ��������." << endl;
    }
}

// ��������, ��� ������ � ����� �� 0 �� 99 (��� ������)
bool Money::isValidShortInt(const string& s)
{
    if (!isValidUnsignedInt(s)) return false;

    try {
        unsigned long val = std::stoul(s);
        if (val <= 99)
            return true;
        else
            return false;
    }
    catch (...) {
        return false;
    }
}

// ���� short int (������) � ��������� � �������� ������� ��� ������
short int Money::inputShortInt(const string& prompt)
{
    string line;
    while (true)
    {
        cout << prompt;
        getline(cin, line);

        if (isValidShortInt(line))
        {
            try {
                unsigned long val = std::stoul(line);
                if (val <= 99)
                    return static_cast<short int>(val);
            }
            catch (...) {}
        }
        cout << "������: ������� ����� �� 0 �� 99 ��� ������ ��������." << endl;
    }
}