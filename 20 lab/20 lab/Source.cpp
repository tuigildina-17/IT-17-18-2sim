#include "Header.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
using namespace std;

//Задача 1 (1 и 3)
double readDouble(const string& prompt) 
{
    while (true) 
    {
        cout << prompt;
        string line;
        getline(cin, line);

        if (line.empty()) 
        {
            cout << "Ошибка: ввод пустой. Попробуйте снова.\n";
            continue;
        }

        stringstream ss(line);
        double value;
        char leftover;
        if (!(ss >> value) || (ss >> leftover)) 
        {
            cout << "Ошибка: введите корректное число.\n";
            continue;
        }

        return value;
    }
}

Point::Point() : x(0), y(0)
{
}
Point::Point(double _x, double _y) : x(_x), y(_y)
{
}

void Point::setX(double _x)
{
    x = _x;
}
void Point::setY(double _y)
{
    y = _y;
}

double Point::getX() const
{
    return x;
}
double Point::getY() const
{
    return y;
}

string Point::toString() const
{
    return "{" + to_string(x) + ";" + to_string(y) + "}";
}

void Point::print() const
{
    cout << toString() << endl;
}
//_____________________________________________________________________________//

Name::Name() : lastName(""), firstName(""), patronymic("") 
{
}
Name::Name(const string& LastName, const string& FirstName, const string& Patronymic) : lastName(LastName), firstName(FirstName), patronymic(Patronymic) 
{
}

void Name::setLastName(const string& LastName) 
{
    lastName = LastName; 
}
void Name::setFirstName(const string& FirstName) 
{ 
    firstName = FirstName; 
}
void Name::setPatronymic(const string& Patronymic) 
{ 
    patronymic = Patronymic; 
}

string Name::toString() const 
{
    string result;
    if (!lastName.empty()) result += lastName;
    if (!firstName.empty()) 
    {
        if (!result.empty()) result += " ";
        result += firstName;
    }
    if (!patronymic.empty()) 
    {
        if (!result.empty()) result += " ";
        result += patronymic;
    }
    return result;
}

void Name::print() const 
{
    cout << toString() << endl;
}

//Задача 2 (1)
Line::Line() : start(Point()), end(Point())
{
}
Line::Line(const Point& _start, const Point& _end) : start(_start), end(_end)
{
}

void Line::setStart(const Point& _start)
{
    start = _start;
}
void Line::setEnd(const Point& _end)
{
    end = _end;
}

const Point& Line::getStart() const
{
    return start;
}
const Point& Line::getEnd() const
{
    return end;
}

string Line::toString() const
{
    return "Линия от точки " + start.toString() + " до точки " + end.toString();
}

void Line::print() const
{
    cout << toString() << endl;
}


LineDependent::LineDependent(const Point* _startRef, const Point* _endRef) : startRef(_startRef), endRef(_endRef)
{
}

string LineDependent::toString() const
{
    return "Линия от точки " + startRef->toString() + " до точки " + endRef->toString();
}

void LineDependent::print() const
{
    cout << toString() << endl;
}

//Задача 3 (3) и Задача 4 (8)
City::City(const string& cityName) : name(cityName) 
{
}

City::City(const string& cityName, const map<City*, int>& connectedPaths) : name(cityName) 
{
    for (auto& p : connectedPaths) 
    {
        if (p.second >= 0)
            paths[p.first] = p.second;
        else
            cout << "Стоимость пути не может быть отрицательной\n";
    }
}

string City::getName() const 
{
    return name;
}

void City::addPath(City* destination, int cost, bool bidirectional) 
{
    if (cost < 0) 
    {
        cout << "Стоимость пути не может быть отрицательной" << endl;
        return;
    }
    paths[destination] = cost;
    if (bidirectional) 
    {
        destination->paths[this] = cost;
    }
}

void City::print() const 
{
    cout << "Город: " << name << "\nПути:\n";
    for (const auto& p : paths) 
    {
        cout << "  " << p.first->name << ": " << p.second << endl;
    }
}

//Задача 5 (5)
int Fraction::gcd(int a, int b) 
{
    while (b != 0) 
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a < 0 ? -a : a;
}

void Fraction::reduce() 
{
    int g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
    if (denominator < 0) 
    {
        denominator = -denominator;
        numerator = -numerator;
    }
}

Fraction::Fraction(int n, int d) : numerator(n), denominator(d) 
{
    if (denominator == 0) throw invalid_argument("Знаменатель не может быть равен нулю");
    reduce();
}

string Fraction::toString() const 
{
    return to_string(numerator) + "/" + to_string(denominator);
}

void Fraction::print() const 
{
    cout << toString();
}

Fraction Fraction::sum(const Fraction& other) const 
{
    int n = numerator * other.denominator + other.numerator * denominator;
    int d = denominator * other.denominator;
    return Fraction(n, d);
}

Fraction Fraction::sum(int value) const 
{
    return sum(Fraction(value));
}

Fraction Fraction::minus(const Fraction& other) const 
{
    int n = numerator * other.denominator - other.numerator * denominator;
    int d = denominator * other.denominator;
    return Fraction(n, d);
}

Fraction Fraction::minus(int value) const 
{
    return minus(Fraction(value));
}

Fraction Fraction::mul(const Fraction& other) const 
{
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::mul(int value) const 
{
    return Fraction(numerator * value, denominator);
}

Fraction Fraction::div(const Fraction& other) const 
{
    if (other.numerator == 0) throw invalid_argument("Деление на нулевую дробь");
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

Fraction Fraction::div(int value) const 
{
    if (value == 0) throw invalid_argument("Деление целого числа на ноль");
    return Fraction(numerator, denominator * value);
}

int readInt(const string& prompt) 
{
    int value;
    while (true) 
    {
        cout << prompt;
        string input;
        getline(cin, input);

        size_t start = 0;
        if (input.empty()) 
        {
            cout << "Ошибка: ввод пустой. Попробуйте снова.\n";
            continue;
        }

        if (input[0] == '-') 
        {
            if (input.size() == 1) 
            {
                cout << "Ошибка: после знака минус должны быть цифры. Попробуйте снова.\n";
                continue;
            }
            start = 1;
        }

        bool valid = true;
        for (size_t i = start; i < input.size(); ++i) 
        {
            if (!isdigit(input[i])) 
            {
                valid = false;
                break;
            }
        }

        if (!valid) 
        {
            cout << "Ошибка: ввод содержит недопустимые символы. Попробуйте снова.\n";
            continue;
        }

        try 
        {
            int value = stoi(input);
            return value;
        }
        catch (const exception&) 
        {
            cout << "Ошибка преобразования числа. Попробуйте снова.\n";
        }
    }
}