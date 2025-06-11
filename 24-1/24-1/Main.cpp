#include "Code.h"

int main() 
{
    setlocale(LC_ALL, "ru");
    string message;
    int choice;
    cout << "Выберите способ ввода:\n1. С клавиатуры\n2. Из файла\n3. Случайные числа\n";
    cin >> choice;

    HammingCode hamming("");

    switch (choice) 
    {
    case 1:
        hamming.inputFromKeyboard(message); // Ввод с клавиатуры
        break;
    case 2:
        hamming.inputFromFile(message); // Ввод из файла
        break;
    case 3:
        int length;
        cout << "Введите длину случайного сообщения: ";
        cin >> length;
        hamming.inputRandom(message, length); // Генерация случайного сообщения
        break;
    default:
        cout << "Неверный выбор!" << endl;
        return 1; // Завершение программы в случае неверного выбора
    }

    cout << "Полученное сообщение: " << message << endl;

    hamming = HammingCode(message);

    string encodedMessage = hamming.encode();

    cout << "Закодированное сообщение: " << encodedMessage << endl;

    // Ввод ошибки от пользователя
    int errorBit;
    cout << "Введите номер бита (начиная с 1), в котором хотите внести ошибку (0 для пропуска): ";
    cin >> errorBit;

    if (errorBit > 0) {
        // Вносим ошибку в закодированное сообщение
        encodedMessage[errorBit - 1] = (encodedMessage[errorBit - 1] == '0') ? '1' : '0';
        cout << "Сообщение с внесенной ошибкой: " << encodedMessage << endl;

        // Проверка и исправление ошибки
        string correctedMessage = hamming.correct(encodedMessage);
        cout << "Исправленное сообщение: " << correctedMessage << endl;
    }
    else {
        cout << "Ошибка не внесена." << endl;
    }

    return 0;
}
