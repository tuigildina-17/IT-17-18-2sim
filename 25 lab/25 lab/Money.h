//1. Спроектировать класс, предусмотрев возможные варианты использования.Реализовать
//определение класса(поля, свойства, конструкторы(не менее трех), перегрузку оператора
//    вывода для вывода полей, заданный метод согласно варианту).Протестировать все методы,
//    включая конструкторы(не забывайте проверять вводимые пользователем данные
//        на корректность).
//    Money 
//    unsigned int rubles
//    short int kopeks
//    Сравнение двух объектов типа
//    Money.Результат должен быть типа
//    bool.
//2. Добавить к реализованному в первом задании классу указанные в варианте перегруженные
//операции.Протестировать все операции
//Унарные операции :
//--вычитание копейки из объекта типа Money
//++ добавление копейки к объекту типа Money
//Операции приведения типа :
//unsigned int(неявная) результатом является количество
//рублей(копейки отбрасываются);
//double(явная) результатом является копейки, переведенные в
//рубли, целые рубли отбрасываются, результат < 1.
//    Бинарные операции :
//-Money m – вычитание сумм
//- целое число – вычитание копеек из денежной суммы

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

    void normalize(); // Приведение к нормальному виду (например, если kopeks >= 100)

public:
    // Конструкторы
    Money(); // по умолчанию - 0 рублей 0 копеек
    Money(unsigned int r); // рубли, копейки = 0
    Money(unsigned int r, short int k); // рубли и копейки
    Money(const Money& other); // Копирование
    static Money createCopy(const Money& other);

    // Геттеры
    unsigned int getRubles() const;
    short int getKopeks() const;

    // Сеттеры с проверкой корректности
    void setRubles(unsigned int r);
    bool setKopeks(short int k); // возвращает false, если некорректно

    // Метод сравнения двух объектов Money
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Money& m);


    // Операторы для 2 задания

    // Унарные ++ (префикс)
    Money& operator++();

    // Унарные ++ (постфикс)
    Money operator++(int);

    // Унарные -- (префикс)
    Money& operator--();

    // Унарные -- (постфикс)
    Money operator--(int);

    // Операции приведения типов
    operator unsigned int() const;   // неявное приведение к рублям (без копеек)
    explicit operator double() const; // явное приведение к дробным рублям

    // Бинарные операции вычитания
    Money operator-(const Money& other) const;
    Money operator-(int kopeks) const;

    // Функции для проверки и ввода
    static bool isValidUnsignedInt(const string& s);
    static unsigned int inputUnsignedInt(const string& prompt);

    static bool isValidShortInt(const string& s);
    static short int inputShortInt(const string& prompt);
};

#endif
