#include "Money.h"

// Нормализация: если kopeks >= 100, переводим лишние копейки в рубли
void Money::normalize() 
{
    if (kopeks < 0) 
    {
        // Если отрицательное значение копеек, устанавливаем в 0 (защита от некорректных данных)
        kopeks = 0;
    }
    if (kopeks >= 100) 
    {
        rubles += kopeks / 100; // Переводим каждую сотню копеек в 1 рубль
        kopeks = kopeks % 100; // Оставшиеся копейки после перевода в рубли
    }
}


// Конструкторы

// Конструктор по умолчанию: сумма 0 руб. 0 коп.
Money::Money() : rubles(0), kopeks(0) 
{
}

// Конструктор с указанием только рублей, копейки по умолчанию 0
Money::Money(unsigned int r) : rubles(r), kopeks(0) 
{
}

// Конструктор с указанием рублей и копеек, с вызовом нормализации
Money::Money(unsigned int r, short int k) : rubles(r), kopeks(k) 
{
    normalize(); // Обеспечиваем корректное состояние объекта
}

// Конструктор копирования
Money::Money(const Money& other) : rubles(other.rubles), kopeks(other.kopeks)
{
}

Money Money::createCopy(const Money& other) 
{
    return Money(other);
}

// Геттеры - методы для получения значений полей

unsigned int Money::getRubles() const 
{
    return rubles; // Возвращаем количество рублей
}

short int Money::getKopeks() const 
{
    return kopeks; // Возвращаем количество копеек
}


// Сеттеры — методы для установки значений полей

void Money::setRubles(unsigned int r) 
{
    rubles = r; // Устанавливаем значение рублей без ограничений
}

bool Money::setKopeks(short int k) 
{
    // Проверяем корректность значения копеек: должно быть от 0 до 99 включительно
    if (k < 0 || k >= 100) 
    {
        return false; // некорректное значение
    }
    kopeks = k; // Устанавливаем значение копеек
    return true; // Успешно
}


// Операторы сравнения

// Проверка равенства двух объектов Money (рубли и копейки должны совпадать)
bool Money::operator==(const Money& other) const 
{
    return (rubles == other.rubles) && (kopeks == other.kopeks);
}

// Проверка неравенства 
bool Money::operator!=(const Money& other) const 
{
    return !(*this == other);
}


// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const Money& m) 
{
    os << m.rubles << " руб. " << m.kopeks << " коп.";
    return os;
}


// Операторы для 2 задания

// Префикс ++ (добавляем 1 копейку)
Money& Money::operator++()
{
    kopeks++;
    normalize();
    return *this;
}

// Постфикс ++ (добавляем 1 копейку, возвращаем старое значение)
Money Money::operator++(int)
{
    Money temp = *this;
    ++(*this);
    return temp;
}

// Префикс -- (вычитаем 1 копейку)
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
            // Уже 0 рублей и 0 копеек - ничего не меняем
            kopeks = 0;
        }
    }
    else
        kopeks--;
    return *this;
}

// Постфикс -- (вычитаем 1 копейку, возвращаем старое значение)
Money Money::operator--(int)
{
    Money temp = *this;
    --(*this);
    return temp;
}

// Неявное приведение к unsigned int — количество рублей без копеек
Money::operator unsigned int() const
{
    return rubles;
}

// Явное приведение к double — рубли + дробная часть из копеек
Money::operator double() const
{
    return rubles + kopeks / 100.0;
}

// Вычитание двух сумм
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

// Вычитание копеек из суммы
Money Money::operator-(int k) const
{
    int totalKopeks = static_cast<int>(rubles) * 100 + kopeks;
    int diff = totalKopeks - k;

    if (diff < 0) diff = 0;

    unsigned int newRubles = diff / 100;
    short int newKopeks = diff % 100;

    return Money(newRubles, newKopeks);
}


// Проверка, что строка — неотрицательное целое число (без лишних символов)
bool Money::isValidUnsignedInt(const string& s)
{
    if (s.empty()) return false;
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

// Ввод unsigned int с проверкой и повтором запроса при ошибке
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
        cout << "Ошибка: введите неотрицательное целое число без лишних символов." << endl;
    }
}

// Проверка, что строка — число от 0 до 99 (для копеек)
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

// Ввод short int (копеек) с проверкой и повтором запроса при ошибке
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
        cout << "Ошибка: введите число от 0 до 99 без лишних символов." << endl;
    }
}