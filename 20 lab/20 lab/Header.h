#ifndef HEADER_H
#define HEADER_H
#include <string>
#include <map>
using namespace std;

// 1
class Point
{
private:
    double x;
    double y;
public:
    Point();
    Point(double _x, double _y);

    void setX(double _x);
    void setY(double _y);

    double getX() const;
    double getY() const;

    string toString() const;
    void print() const;
};

class Name
{
private:
    string lastName;
    string firstName;
    string patronymic;
public:
    Name();
    Name(const string& LastName, const string& FirstName, const string& Patronymic);

    void setLastName(const string& LastName);
    void setFirstName(const string& FirstName);
    void setPatronymic(const string& Patronymic);

    string toString() const;
    void print() const;
};

// 2
class Line
{
private:
    Point start;
    Point end;
public:
    Line();
    Line(const Point& _start, const Point& _end);

    void setStart(const Point& _start);
    void setEnd(const Point& _end);

    const Point& getStart() const;
    const Point& getEnd() const;

    string toString() const;
    void print() const;
};

class LineDependent
{
private:
    const Point* startRef;
    const Point* endRef;
public:
    LineDependent(const Point* _startRef, const Point* _endRef);

    string toString() const;
    void print() const;
};

// 3 è 4
class City {
private:
    string name;
    map<City*, int> paths;

public:
    City(const string& cityName);
    City(const string& cityName, const map<City*, int>& connectedPaths);
    string getName() const;
    void addPath(City* destination, int cost, bool bidirectional = false);
    void print() const;
};

// 5
class Fraction {
private:
    int numerator;
    int denominator;

    static int gcd(int a, int b);
    void reduce();

public:
    Fraction(int n = 0, int d = 1);

    string toString() const;
    void print() const;

    Fraction sum(const Fraction& other) const;
    Fraction sum(int value) const;
    Fraction minus(const Fraction& other) const;
    Fraction minus(int value) const;
    Fraction mul(const Fraction& other) const;
    Fraction mul(int value) const;
    Fraction div(const Fraction& other) const;
    Fraction div(int value) const;
};

int readInt(const string& prompt);
double readDouble(const string& prompt);

#endif