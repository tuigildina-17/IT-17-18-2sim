//Имеется набор сообщений.Для данного сообщения построить код Хемминга, который
//позволит обнаруживать одиночную ошибку и исправлять ее.Написать программу и привести
//решение «вручную», в котором виден процесс построения кодов(рекомендуется использовать
//    электронные таблицы).

#ifndef CODE_H
#define CODE_H

#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class HammingCode 
{
public:
    HammingCode(const string& data);
    string encode();
    string correct(string encodedMessage);
    int findError(const string& encodedMessage);

    void inputFromKeyboard(string& message);
    void inputFromFile(string& message);
    void inputRandom(string& message, int length);

private:
    string data;
    int calculateParityBits();
    void fillData(string& code, int r);
};

#endif
