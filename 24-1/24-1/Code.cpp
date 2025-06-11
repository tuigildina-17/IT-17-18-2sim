#include "Code.h"

// Конструктор класса
HammingCode::HammingCode(const string& data) : data(data) 
{
}

// Метод для вычисления количества контрольных битов, необходимых для кодирования данных
int HammingCode::calculateParityBits() 
{
    int m = data.length(); // Длина входных данных
    int r = 0; // Количество контрольных битов

    // Определяем количество контрольных битов r
    // Условие: 2^r >= m + r + 1
    // Это условие гарантирует, что у нас достаточно контрольных битов для кодирования данных
    while (pow(2, r) < (m + r + 1)) 
    {
        r++; // Увеличиваем количество контрольных битов, пока условие не выполнится
    }
    return r; // Возвращаем рассчитанное количество контрольных битов
}

// Метод для заполнения строки кода данными и местами для контрольных битов
void HammingCode::fillData(string& code, int r) 
{
    int j = 0; // Индекс для прохода по исходным данным
    int codeLength = data.length() + r; // Общая длина кода (данные + контрольные биты)

    // Заполняем строку кода
    for (int i = 1; i <= codeLength; i++) 
    {
        // Проверяем, является ли i степенью двойки (позиция контрольного бита)
        if (i & (i - 1)) // Если i - не степень двойки
        { 
            code[i - 1] = data[j++]; // Заполняем код данными из исходной строки
        }
        else 
        {
            code[i - 1] = 'P'; // Место для контрольного бита
        }
    }
}

// Метод для кодирования данных с использованием кода Хэмминга
string HammingCode::encode() 
{
    // Вычисляем количество бит проверки 
    int r = calculateParityBits();
    // Определяем общую длину кодируемого сообщения
    int codeLength = data.length() + r;
    // Инициализируем строку кодового слова нулями
    string code(codeLength, '0');

    fillData(code, r); // Заполняем данные в кодовом слове, оставляя место для бит проверким

    // Для каждого бита проверки
    for (int i = 0; i < r; i++) 
    {
        int parityPos = (1 << i) - 1;
        int parityValue = 0;

        // Проверяем все позиции в кодовом слове для вычисления значения бита проверки
        for (int j = 1; j <= codeLength; j++) 
        {
            // Если позиция j включает бит проверки
            if (j & (parityPos + 1)) 
            {
                // Если текущая позиция не является позицией бита проверки
                if (code[j - 1] != 'P') 
                {
                    parityValue ^= (code[j - 1] - '0'); // Преобразуем символ в число
                }
            }
        }
        // Устанавливаем вычисленное значение бита проверки в соответствующую позицию
        code[parityPos] = parityValue + '0';
    }

    return code;
}

void HammingCode::inputFromKeyboard(string& message) 
{
    cout << "Введите сообщение (бинарная строка): ";
    cin >> message;

    // Проверка корректности ввода
    for (char c : message) 
    {
        if (c != '0' && c != '1') 
        {
            cout << "Ошибка: сообщение должно содержать только 0 и 1." << endl;
            exit(1);
        }
    }
}

void HammingCode::inputFromFile(string& message) 
{
    ifstream file("a.txt");
    if (!file.is_open()) 
    {
        cout << "Ошибка: не удалось открыть файл a.txt." << endl;
        exit(1);
    }
    getline(file, message);
    file.close();

    // Проверка корректности ввода
    for (char c : message) 
    {
        if (c != '0' && c != '1') 
        {
            cout << "Ошибка: сообщение должно содержать только 0 и 1." << endl;
            exit(1);
        }
    }
}

void HammingCode::inputRandom(string& message, int length) 
{
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    message.clear(); // Очистка строки перед заполнением
    for (int i = 0; i < length; ++i) 
    {
        message += (rand() % 2) ? '1' : '0'; // Генерация случайного бита
    }
}

// Метод для нахождения позиции ошибки
int HammingCode::findError(const string& encodedMessage)
{
    int r = calculateParityBits(); // Вычисляем количество бит четности
    int codeLength = encodedMessage.length(); // Получаем длину закодированного сообщения
    int errorPosition = 0; // Инициализируем позицию ошибки

    for (int i = 0; i < r; i++)
    {
        int parityPos = (1 << i) - 1; // Вычисляем позицию бита четности
        int parityValue = 0; // Инициализируем значение четности

        // Проверяем все биты сообщения, чтобы вычислить значение четности
        for (int j = 1; j <= codeLength; j++) 
        {
            if (j & (parityPos + 1)) // Проверяем, относится ли бит к текущему биту четности
            {
                if (encodedMessage[j - 1] != 'P') // Игнорируем биты четности
                {
                    parityValue ^= (encodedMessage[j - 1] - '0'); // Вычисляем значение четности
                }
            }
        }

        if (parityValue != 0) // Если значение четности не равно нулю, значит, есть ошибка
        {
            errorPosition += parityPos + 1; // Учитываем позицию ошибки
        }
    }

    return errorPosition > 0 ? errorPosition - 1 : -1; // Возвращаем позицию ошибки или -1, если её нет
}

// Метод для исправления ошибки в закодированном сообщении
string HammingCode::correct(string encodedMessage)
{
    int errorPosition = findError(encodedMessage); // Находим позицию ошибки
    if (errorPosition != -1) // Если ошибка найдена
    {
        // Исправляем ошибку, меняя бит на противоположный
        encodedMessage[errorPosition] = (encodedMessage[errorPosition] == '0') ? '1' : '0';
        cout << "Ошибка найдена и исправлена в позиции: " << errorPosition + 1 << endl;
    }
    else
    {
        cout << "Ошибок не найдено." << endl;
    }

    return encodedMessage; // Возвращаем исправленное сообщение
}
