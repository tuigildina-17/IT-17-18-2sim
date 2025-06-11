#include "Code.h"

// ����������� ������
HammingCode::HammingCode(const string& data) : data(data) 
{
}

// ����� ��� ���������� ���������� ����������� �����, ����������� ��� ����������� ������
int HammingCode::calculateParityBits() 
{
    int m = data.length(); // ����� ������� ������
    int r = 0; // ���������� ����������� �����

    // ���������� ���������� ����������� ����� r
    // �������: 2^r >= m + r + 1
    // ��� ������� �����������, ��� � ��� ���������� ����������� ����� ��� ����������� ������
    while (pow(2, r) < (m + r + 1)) 
    {
        r++; // ����������� ���������� ����������� �����, ���� ������� �� ����������
    }
    return r; // ���������� ������������ ���������� ����������� �����
}

// ����� ��� ���������� ������ ���� ������� � ������� ��� ����������� �����
void HammingCode::fillData(string& code, int r) 
{
    int j = 0; // ������ ��� ������� �� �������� ������
    int codeLength = data.length() + r; // ����� ����� ���� (������ + ����������� ����)

    // ��������� ������ ����
    for (int i = 1; i <= codeLength; i++) 
    {
        // ���������, �������� �� i �������� ������ (������� ������������ ����)
        if (i & (i - 1)) // ���� i - �� ������� ������
        { 
            code[i - 1] = data[j++]; // ��������� ��� ������� �� �������� ������
        }
        else 
        {
            code[i - 1] = 'P'; // ����� ��� ������������ ����
        }
    }
}

// ����� ��� ����������� ������ � �������������� ���� ��������
string HammingCode::encode() 
{
    // ��������� ���������� ��� �������� 
    int r = calculateParityBits();
    // ���������� ����� ����� ����������� ���������
    int codeLength = data.length() + r;
    // �������������� ������ �������� ����� ������
    string code(codeLength, '0');

    fillData(code, r); // ��������� ������ � ������� �����, �������� ����� ��� ��� ���������

    // ��� ������� ���� ��������
    for (int i = 0; i < r; i++) 
    {
        int parityPos = (1 << i) - 1;
        int parityValue = 0;

        // ��������� ��� ������� � ������� ����� ��� ���������� �������� ���� ��������
        for (int j = 1; j <= codeLength; j++) 
        {
            // ���� ������� j �������� ��� ��������
            if (j & (parityPos + 1)) 
            {
                // ���� ������� ������� �� �������� �������� ���� ��������
                if (code[j - 1] != 'P') 
                {
                    parityValue ^= (code[j - 1] - '0'); // ����������� ������ � �����
                }
            }
        }
        // ������������� ����������� �������� ���� �������� � ��������������� �������
        code[parityPos] = parityValue + '0';
    }

    return code;
}

void HammingCode::inputFromKeyboard(string& message) 
{
    cout << "������� ��������� (�������� ������): ";
    cin >> message;

    // �������� ������������ �����
    for (char c : message) 
    {
        if (c != '0' && c != '1') 
        {
            cout << "������: ��������� ������ ��������� ������ 0 � 1." << endl;
            exit(1);
        }
    }
}

void HammingCode::inputFromFile(string& message) 
{
    ifstream file("a.txt");
    if (!file.is_open()) 
    {
        cout << "������: �� ������� ������� ���� a.txt." << endl;
        exit(1);
    }
    getline(file, message);
    file.close();

    // �������� ������������ �����
    for (char c : message) 
    {
        if (c != '0' && c != '1') 
        {
            cout << "������: ��������� ������ ��������� ������ 0 � 1." << endl;
            exit(1);
        }
    }
}

void HammingCode::inputRandom(string& message, int length) 
{
    srand(static_cast<unsigned int>(time(0))); // ������������� ���������� ��������� �����
    message.clear(); // ������� ������ ����� �����������
    for (int i = 0; i < length; ++i) 
    {
        message += (rand() % 2) ? '1' : '0'; // ��������� ���������� ����
    }
}

// ����� ��� ���������� ������� ������
int HammingCode::findError(const string& encodedMessage)
{
    int r = calculateParityBits(); // ��������� ���������� ��� ��������
    int codeLength = encodedMessage.length(); // �������� ����� ��������������� ���������
    int errorPosition = 0; // �������������� ������� ������

    for (int i = 0; i < r; i++)
    {
        int parityPos = (1 << i) - 1; // ��������� ������� ���� ��������
        int parityValue = 0; // �������������� �������� ��������

        // ��������� ��� ���� ���������, ����� ��������� �������� ��������
        for (int j = 1; j <= codeLength; j++) 
        {
            if (j & (parityPos + 1)) // ���������, ��������� �� ��� � �������� ���� ��������
            {
                if (encodedMessage[j - 1] != 'P') // ���������� ���� ��������
                {
                    parityValue ^= (encodedMessage[j - 1] - '0'); // ��������� �������� ��������
                }
            }
        }

        if (parityValue != 0) // ���� �������� �������� �� ����� ����, ������, ���� ������
        {
            errorPosition += parityPos + 1; // ��������� ������� ������
        }
    }

    return errorPosition > 0 ? errorPosition - 1 : -1; // ���������� ������� ������ ��� -1, ���� � ���
}

// ����� ��� ����������� ������ � �������������� ���������
string HammingCode::correct(string encodedMessage)
{
    int errorPosition = findError(encodedMessage); // ������� ������� ������
    if (errorPosition != -1) // ���� ������ �������
    {
        // ���������� ������, ����� ��� �� ���������������
        encodedMessage[errorPosition] = (encodedMessage[errorPosition] == '0') ? '1' : '0';
        cout << "������ ������� � ���������� � �������: " << errorPosition + 1 << endl;
    }
    else
    {
        cout << "������ �� �������." << endl;
    }

    return encodedMessage; // ���������� ������������ ���������
}
