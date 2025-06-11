#include "Tree.h"

int main()
{
    setlocale(LC_ALL, "ru");
    BinarySearchTree tree;
    vector<int> values;

    int choice;
    while (true)
    {
        cout << "�������� ������ ���������� ������:\n";
        cout << "1. � ����������\n2. �� �����\n3. ���������� �������\n";
        choice = readInt("��� �����: ");
        if (choice >= 1 && choice <= 3)
            break;
        cout << "������������ �����. ���������� ��� ���.\n";
    }

    if (choice == 1)
    {
        int n;
        while (true)
        {
            n = readInt("������� ����� ������ ������? ");
            if (n > 0) 
                break;
            cout << "������� ������������� �����.\n";
        }
        cout << "������� ����� (����� Enter):\n";
        int count = 0;
        while (count < n)
        {
            int val = readInt("");
            values.push_back(val);
            tree.insert(val);
            count++;
        }
    }
    else if (choice == 2)
    {
        ifstream fin("a.txt");
        if (!fin.is_open())
        {
            cout << "�� ������� ������� ����\n";
            return 1;
        }
        string line;
        while (getline(fin, line))
        {
            if (line.empty()) 
                continue;
            stringstream ss(line);
            int val;
            while (ss >> val)
            {
                values.push_back(val);
                tree.insert(val);
            }
        }
        fin.close();
        if (values.empty())
        {
            cout << "���� ���� ��� �������� ������������ ������\n";
            return 1;
        }
    }
    else if (choice == 3)
    {
        int n;
        while (true)
        {
            n = readInt("������� ��������� ����� �������? ");
            if (n > 0) 
                break;
            cout << "������� ������������� �����.\n";
        }
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < n; ++i)
        {
            int val = 1 + rand() % 100;
            values.push_back(val);
            tree.insert(val);
        }
    }

    printValues(values);

    cout << "������:\n";
    tree.printTree();

    try
    {
        cout << "\n������������ �������� � ������: " << tree.findMax() << "\n";
    }
    catch (exception& e)
    {
        cout << "������: " << e.what() << "\n";
    }

    return 0;
}