#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
/// <summary>
/// ���� ��������� ��������� �� �������� ���� ����� ��� ��������� �� ���� � �������������� � int
/// </summary>
/// <param name="t"> ��������������� ���� </param>
/// <returns></returns>
bool unitTest_CorrectByte(int t) {
    return t < 256 ? 1 : 0;
}

/// <summary>
/// ����������� char � int � ������� ���������� ���������� ������, �������� ��������� � ������
/// </summary>
/// <param name="t"> ����� </param>
/// <param name="mass"> ������ �� ������ � ������� � ���������� ����� </param>
/// <returns></returns>
bool ByteIdentity(char t, int* mass) {
    int num = 0;
    char m = 1 << (sizeof(char) * 8 - 1);


    for (int i = 0; i < sizeof(char) * 8; ++i)
    {
        num += pow(2, 7 - i) * (t & m ? 1 : 0);
        t <<= 1;
    }
    mass[num] += 1;

    /*
    if (unitTest_CorrectByte(num))
        cout << num << endl;
    else {
        cout << "Error";
        return false;
    }
    */

    return true;
}
/// <summary>
/// ���������: 
/// 1) ������� ������ � ����� 2) ������� ��������� ������� �����
/// </summary>
/// <returns></returns>
bool exersiseOne() {
    int countByte = 0;
    int counter = 0;
    char ch;
    int* countAnyByteMass = new int[256];


    for (int i = 0; i < 256; i++) {
        countAnyByteMass[i] = 0;
    }

    ifstream fin("lab1.docx", ios::binary);
    if (!fin)
    {
        cout << "File don't open" << endl;
        system("pause");
        return false;
    }

    fin.seekg(0, ios_base::end);
    countByte = fin.tellg();
    fin.seekg(0, ios_base::beg);


    char* massByte = new char[countByte];


    while (fin.get(ch)) {
        if (!ByteIdentity(ch, countAnyByteMass))
            return false;
        massByte[counter] = ch;
        counter++;
    }

    cout << " ���������� ���� = " << countByte << endl << endl;

    counter = 0;
    for (int i = 0; i < 256; i++) {
        cout << " ���������� ������ ������ '" << i << "' " << countAnyByteMass[i] << ". ��� " << ((double)countAnyByteMass[i] / countByte) * 100 << "%" << endl;
        counter += countAnyByteMass[i];
    }

    if (counter == countByte)
        cout << "\n ���������� " << counter << "\n ��������� � ����������� ����������� ��������x ������\n";
    else {
        cout << "\n ����� ���������� ������\n" << " ������� " << countByte << "\n" << " ���������� " << counter << endl;
    }
    fin.close();

    
    delete[](countAnyByteMass);
    return true;
}
/// <summary>
/// ���������: 1) ���������� �����, ������ � ������ �������������� � ����. 2)���������� �����, ������, ����� �� ����� ��������������� ������
/// </summary>
/// <returns></returns>
bool exersiseTwo() {
    int choose;
    bool flag;

    while (true) {
        flag = true;

        cout << "\n �������� �������" << endl;
        cout << " 1. �����������" << endl;
        cout << " 2. ������������" << endl;
        cout << " 3. �����" << endl << endl;
        cout << " ";


        while (flag)
        {
            cout << "������� �� ����: ";
            cin >> choose;

            switch (choose)
            {
            case 1: {
                char ch;
                char str[4];
                int key;               


                ifstream key_file("key.txt");                               
                ifstream in("input.txt");
                ofstream out("output.txt");
                
                if (!key_file || !in || !out)
                {
                    cout << "File don't open!" << endl;
                    system("pause");
                    return false;
                }

                key_file.getline(str, 4);
                key = atoi(str);

                while (in.get(ch)) { // ��������� ��� ����� ����� �� ������� 256
                    printf(" %c -> %c\n", ch, (ch + key) % 256);
                    out << (char) ((ch + key) % 256);
                }               

                key_file.close();
                in.close();
                out.close();
                flag = false;
                break;
            }
            case 2: {
                char ch;
                char str[4];
                int key;
                string ans = "";

                ifstream key_file("key.txt");                              
                ifstream in("output.txt");

                if (!key_file || !in)
                {
                    cout << "File don't open!" << endl;
                    system("pause");
                    return false;
                }

                key_file.getline(str, 4);
                key = atoi(str);

                while (in.get(ch)) { // ��������� ��� ����� ����� �� ������� 256
                    printf(" %c -> %c\n", ch, (ch - key) % 256);
                    ans += (char)((ch - key) % 256);
                }

                cout << ans << endl;
                key_file.close();
                in.close();
                flag = false;
                break;
            }
            case 3: {
                return true;
            }
            default:
                cout << " ������ �����, ��������� �������" << endl;
                break;
            }
        }
    }

    
}

bool lab1() {
    setlocale(LC_ALL, "rus");
    int choose; 
    bool flag;

    while (true) {
        flag = true;


        cout << "\n �������� �������" << endl;
        cout << " 1. �������� �������" << endl;
        cout << " 2. �����������������" << endl;
        cout << " 3. �����" << endl << endl;
        cout << " ";

        while (flag)
        {
            cout << "������� �� ����: ";
            cin >> choose;

            switch (choose)
            {
            case 1: {
                if (!exersiseOne())
                    return false;
                
                flag = false;
                break;
            }
            case 2: {
                if (!exersiseTwo())
                    return false;
                flag = false;
                break;
            }
            case 3: {
                return true;
            }
            default:
                cout << " ������ �����, ��������� �������" << endl;
                break;
            }
        }
    }
}
