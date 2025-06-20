﻿#include "Money.h"

int main() 
{
    setlocale(LC_ALL, "ru");

    // Создание объектов Money разными способами и тест конструкторов
    Money m1; // по умолчанию: 0 руб. 0 коп.
    Money m2(123); // только рубли: 123 руб. 0 коп.
    Money m3(45, 67); // рубли и копейки: 45 руб. 67 коп.
    Money m4(10, 150); // копейки > 99, проверка нормализации (перевод в рубли)
    // Используем конструкор копирования
    Money m44 = Money::createCopy(m4);
    Money m33(m3);

    cout << "Тест конструкторов класса Money:" << endl;
    cout << "m1 (по умолчанию): " << m1 << endl;
    cout << "m2 (только рубли): " << m2 << endl;
    cout << "m3 (рубли и копейки): " << m3 << endl;
    cout << "m4 (с нормализацией копеек > 99): " << m4 << endl;
    cout << "m44 (скопированное значение m4): " << m44 << endl;
    cout << "m33 (скопированное значение m3): " << m33 << endl << endl;

    // Тест сеттеров с проверкой корректности ввода копеек
    Money m5;
    m5.setRubles(50); // устанавливаем рубли в 50

    short int k = Money::inputShortInt("Введите количество копеек для суммы m5 (от 0 до 99): ");
    m5.setKopeks(k);

    cout << "Введённая сумма m5: " << m5 << endl << endl;

    // Тест операторов сравнения
    Money a(6, 50);
    Money b(6, 50);
    Money c(6, 51);

    cout << "Тест сравнения объектов Money:" << endl;
    cout << "a = " << a << ", b = " << b << ", c = " << c << endl;

    cout << "Равны ли a и b? " << (a == b ? "Да" : "Нет") << endl;
    cout << "Не равны ли a и c? " << (a != c ? "Да" : "Нет") << endl;

    cout << "\nТест операторов ++ и --:" << endl;


    // Тесты 2 задания

    // Создаем объект Money
    Money balance(1, 99);
    cout << "Исходное значение balance: " << balance << endl;

    // Префиксный инкремент: сначала увеличиваем на 1 копейку, потом выводим результат
    cout << "Префиксный ++balance (увеличиваем на 1 копейку): " << ++balance << endl;

    // Постфиксный инкремент: сначала выводим текущее значение, потом увеличиваем на 1 копейку
    cout << "Постфиксный balance++ (сначала вывод, потом увеличение): " << balance++ << endl;

    // Выводим значение после постфиксного увеличения
    cout << "Значение после постфиксного balance++: " << balance << endl;

    // Префиксный декремент: сначала уменьшаем на 1 копейку, потом выводим результат
    cout << "Префиксный --balance (уменьшаем на 1 копейку): " << --balance << endl;

    // Постфиксный декремент: сначала выводим текущее значение, потом уменьшаем на 1 копейку
    cout << "Постфиксный balance-- (сначала вывод, потом уменьшение): " << balance-- << endl;

    // Значение после постфиксного уменьшения
    cout << "Значение после постфиксного balance--: " << balance << endl;

    cout << "\nТест приведения типов:" << endl;
    Money m6(12, 34);

    // Неявное приведение к unsigned int — получаем только рубли
    unsigned int rub = m6;

    // Явное приведение к double — получаем сумму в рублях с дробной частью
    double full = static_cast<double>(m6);

    cout << "Объект m6 содержит: " << m6 << endl;
    cout << "Рубли из m6 (unsigned int): " << rub << endl;
    cout.precision(2);
    cout << fixed;
    cout << "Полная сумма из m6 (double): " << full << " руб." << endl;

    cout << "\nТест операторов вычитания:" << endl;
    Money m7(10, 50);
    Money m8(3, 75);

    // Вычитаем один объект Money из другого
    Money diff1 = m7 - m8;
    cout << m7 << " минус " << m8 << " равно " << diff1 << endl;
    cout << endl;

    // Ввод первого объекта
    unsigned int r1 = Money::inputUnsignedInt("Введите рубли первого объекта: ");
    short k1 = Money::inputShortInt("Введите копейки первого объекта: ");
    Money m77(r1, k1);

    // Ввод второго объекта
    unsigned int r2 = Money::inputUnsignedInt("Введите рубли второго объекта: ");
    short k2 = Money::inputShortInt("Введите копейки второго объекта: ");
    Money m88(r2, k2);

    // Вычитание двух объектов
    Money diff11 = m77 - m88;
    cout << m77 << " минус " << m88 << " равно " << diff11 << endl;
    cout << endl;


    // Вычитаем 60 копеек из результата
    Money diff2 = diff11 - 60;
    cout << diff11 << " минус 60 копеек равно " << diff2 << endl;

    // Ввод нового объекта для вычитания копеек
    unsigned int r3 = Money::inputUnsignedInt("\nВведите рубли нового объекта: ");
    short k3 = Money::inputShortInt("Введите копейки нового объекта: ");
    Money m9(r3, k3);

    unsigned int kopToSubtract = Money::inputUnsignedInt("Введите количество копеек, которое нужно вычесть из этого объекта: ");
    cout << endl;

    Money diff22 = m9 - static_cast<int>(kopToSubtract);

    cout << m9 << " минус " << kopToSubtract << " копеек равно " << diff22 << endl;


    // Пытаемся вычесть очень большую сумму (10000 копеек = 100 рублей)
    // Проверяется, что результат не станет отрицательным
    Money diff3 = diff22 - 100000000;
    cout << diff22 << " минус 10000 копеек равно " << diff3 << endl;

    return 0;
}
