#include <iostream>
#include "Header.h"
#include <limits>
#include <sstream>
#include <string>

using namespace std;

int main() 
{
    setlocale(LC_ALL, "ru");

    cout << "Задача 1 (1 и 3):" << endl;
    Point p1(1.5, -2.3);
    Point p2(0, 0);
    Point p3(-7.8, 3.14);

    
    double x = readDouble("Введите x: ");
    double y = readDouble("Введите y: ");
    cout << "Точки:" << endl;
    Point p4(x, y);
    p4.print();

    p1.print();
    p2.print();
    p3.print();
    cout << endl;

    Name n1("", "Клеопатра", "");
    Name n2("Пушкин", "Александр", "Сергеевич");
    Name n3("Маяковский", "Владимир", "");

    cout << "Имена:" << endl;
    n1.print();
    n2.print();
    n3.print();
    cout << endl;

    cout << "Задача 2 (1):" << endl;
    cout << "Линии:" << endl;

    Point l1_start(1, 3);
    Point l1_end(23, 8);
    Line line1(l1_start, l1_end);

    Point l2_start(5, 10);
    Point l2_end(25, 10);
    Line line2(l2_start, l2_end);

    LineDependent line3(&line1.getStart(), &line2.getEnd());

    line1.print();
    line2.print();
    line3.print();

    // Изменим линию 1
    line1.setStart(Point(10, 20));
    line1.setEnd(Point(30, 40));

    // Изменим линию 2
    line2.setStart(Point(15, 10));
    line2.setEnd(Point(35, 10));

    cout << endl << "После изменения координат линии 1 и 2:" << endl;
    line1.print();
    line2.print();
    line3.print();

    // Изменим координаты линии 1 так, чтобы не изменились координаты линии 3
    Point oldStart = line1.getStart();
    line1.setStart(oldStart);
    line1.setEnd(Point(100, 100));

    cout << endl << "После изменения координат линии 1, не влияющих на линию 3:" << endl;
    line1.print();
    line3.print();
    cout << endl;

    cout << "Задача 3 (3) и Задача 4 (8):" << endl;
    City A("A");
    City B("B");
    City C("C");
    City D("D");
    City E("E");
    City F("F");

    A.addPath(&F, 1, false);
    A.addPath(&B, 5, true);
    A.addPath(&D, 6, true);
    F.addPath(&B, 1, false);
    F.addPath(&E, 2, true);
    D.addPath(&E, 2, false);
    D.addPath(&C, 4, true);
    B.addPath(&C, 3, true);

    City G("G", map<City*, int>{{&A, 7}, { &C,3 }});
    City H("H");

    A.print();
    cout << endl;
    B.print();
    cout << endl;
    C.print();
    cout << endl;
    D.print();
    cout << endl;
    E.print();
    cout << endl;
    F.print();
    cout << endl;
    cout << "Созданные города: " << endl;
    G.print();
    cout << endl;
    H.print();
    cout << endl;

    cout << "Задача 5 (5):" << endl;

    try 
    {
        Fraction f1(1, 3);
        Fraction f2(2, 3);
        Fraction f3(3, 4);

        cout << "f1 = "; f1.print(); cout << endl;
        cout << "f2 = "; f2.print(); cout << endl;
        cout << "f3 = "; f3.print(); cout << endl;

        Fraction rSum = f1.sum(f2);
        f1.print(); cout << " + "; f2.print(); cout << " = "; rSum.print(); cout << endl;

        Fraction rMinus = f3.minus(1);
        f3.print(); cout << " - 1 = "; rMinus.print(); cout << endl;

        Fraction rMul = f1.mul(f2);
        f1.print(); cout << " * "; f2.print(); cout << " = "; rMul.print(); cout << endl;

        Fraction rDiv = f2.div(f3);
        f2.print(); cout << " / "; f3.print(); cout << " = "; rDiv.print(); cout << endl;

        Fraction expr = f1.sum(f2).div(f3).minus(5);
        cout << "((1/3 + 2/3) / 3/4) - 5 = ";
        expr.print();
        cout << endl;

        /*cout << "\nВведите дробь (числитель и знаменатель):\n";
        int n = readInt("Числитель: ");
        int d;
        while (true) {
            d = readInt("Знаменатель (не равен 0): ");
            if (d != 0) break;
            cout << "Знаменатель не может быть 0. Попробуйте снова.\n";
        }
        Fraction fInput(n, d);
        cout << "Введенная дробь: ";
        fInput.print();
        cout << endl;*/

        // Вводим две дроби и выбираем операцию, которую хотим провести между этими двумя дробями
        cout << "Введите первую дробь:\n";
        int n1 = readInt("Числитель: ");
        int d1;
        while (true) {
            d1 = readInt("Знаменатель (не равен 0): ");
            if (d1 != 0) break;
            cout << "Знаменатель не может быть 0. Попробуйте снова.\n";
        }
        Fraction f1Input(n1, d1);

        cout << "Введите вторую дробь:\n";
        int n2 = readInt("Числитель: ");
        int d2;
        while (true) {
            d2 = readInt("Знаменатель (не равен 0): ");
            if (d2 != 0) break;
            cout << "Знаменатель не может быть 0. Попробуйте снова.\n";
        }
        Fraction f2Input(n2, d2);

        cout << "Выберите операцию:\n";
        cout << "1 - Сложение\n";
        cout << "2 - Вычитание\n";
        cout << "3 - Умножение\n";
        cout << "4 - Деление\n";

        int choice;
        while (true) {
            choice = readInt("Ваш выбор: ");
            if (choice >= 1 && choice <= 4) break;
            cout << "Неверный выбор. Попробуйте снова.\n";
        }

        Fraction result;
        switch (choice) {
        case 1:
            result = f1Input.sum(f2Input);
            cout << "Результат сложения: ";
            break;
        case 2:
            result = f1Input.minus(f2Input);
            cout << "Результат вычитания: ";
            break;
        case 3:
            result = f1Input.mul(f2Input);
            cout << "Результат умножения: ";
            break;
        case 4:
            result = f1Input.div(f2Input);
            cout << "Результат деления: ";
            break;
        }

        result.print();
        cout << endl;
    }
    
    catch (exception& ex) 
    {
        cerr << "Ошибка: " << ex.what() << endl;
    }

    return 0;
}