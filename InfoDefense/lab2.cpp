#include <iostream>
#include <fstream>
#include <math.h>
#include <unordered_map>


using namespace std;
typedef unordered_map<char, int> encodeMap;
typedef unordered_map<int, char> decodeMap;

int codeLetter(int ed, int n, int num) {  
    int ans = 1;
    for (int i = 0; i < ed; i++) {
        ans *= num;
        ans %= n;
    }
    return ans;
}

int prostoe_chislo() {
    int a;
    static time_t tval = time(0);
    tval += 10;
    

    srand(tval);
    while (true)
    {
        int z = 0, kol = 0;


        a = rand() % 100 + 2;   
        for (int i = 2; i < a; i++) {
            if (a % i == 1)
                continue;
            if (a % i == 0)
            {
                z = 1;
                break;
            }
        }
        if (z == 0)
            break;        
    }
    return a;
}

bool vzaimnoProstoe(int a, int b) {
    if (b < a) {
        int temp = a;
        a = b;
        b = temp;
    }
    for (int i = 2; i < a + 1; i++) {
        if (a % i == 0) 
            if (b % i == 0)
                return false;      
    }
    
    return true;
}

int prostoe_chislo(int border) {
    int a;
    static time_t tval = time(0);
    tval += 10;


    srand(tval);
    while (true)
    {
        int z = 0, kol = 0;


        a = rand() % border + 2;
        for (int i = 2; i < a; i++) {
            if (a % i == 1)
                continue;
            if (a % i == 0)
            {
                z = 1;
                break;
            }
        }
        if (z == 0)
            break;
    }
    return a;
}

bool generateKey() {
    int k;
    int p, q, n, e, euler;
    double d;


    while (true) {
        k = 1;
        p = prostoe_chislo();
        q = prostoe_chislo();

        cout << " ���� ������� ����� " << p << " " << q << endl;

        n = p * q;
        euler = (p - 1) * (q - 1);
        
        while (true) {
            e = rand() % (n-1) % 100 + 1;           
            if (vzaimnoProstoe(e, euler))
                break;

            if (k == 1000000) {
                cout << " ����� �� �������\n" << endl;
                break;
            }
            k++;
        }        
        if (k == 1000000)
            continue;

        cout << " ���� �������� ������ " << e << " " << n << endl;
        
        while (true) {
            d = (double)(k * euler + 1) / e;
            if (int(d) == d) {
                break;
            }
            if ((int)k == 1000000) {
                cout << " ����� �� �������\n" << endl;
                break;
            }
            k++;
        }
        if ((int)k < 100000)          
            break;        
    }
    cout << " ���� �������� ������ " << d << " " << n << endl;

    ofstream open("lab2/RSA_open.txt");
    ofstream close("lab2/RSA_close.txt");

    if (!open || !close)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    open << e << "\n" << n;
    close << d << "\n" << n;

    open.close();
    close.close();
    return true;
}

bool encrypt() {
#pragma region init
    encodeMap alfabet;
    alfabet['�'] = 1;
    alfabet['�'] = 2;
    alfabet['�'] = 3;
    alfabet['�'] = 4;
    alfabet['�'] = 5;
    alfabet['�'] = 6;
    alfabet['�'] = 7;
    alfabet['�'] = 8;
    alfabet['�'] = 9;
    alfabet['�'] = 10;
    alfabet['�'] = 11;
    alfabet['�'] = 12;
    alfabet['�'] = 13;
    alfabet['�'] = 14;
    alfabet['�'] = 15;
    alfabet['�'] = 16;
    alfabet['�'] = 17;
    alfabet['�'] = 18;
    alfabet['�'] = 19;
    alfabet['�'] = 20;
    alfabet['�'] = 21;
    alfabet['�'] = 22;
    alfabet['�'] = 23;
    alfabet['�'] = 24;
    alfabet['�'] = 25;
    alfabet['�'] = 26;
    alfabet['�'] = 27;
    alfabet['�'] = 28;
    alfabet['�'] = 29;
    alfabet['�'] = 30;
    alfabet['�'] = 31;
    alfabet['�'] = 32;
    alfabet['�'] = 33;
    alfabet[' '] = 34;
    alfabet['0'] = 35;
    alfabet['1'] = 36;
    alfabet['2'] = 37;
    alfabet['3'] = 38;
    alfabet['4'] = 39;
    alfabet['5'] = 40;
    alfabet['6'] = 41;
    alfabet['7'] = 42;
    alfabet['8'] = 43;
    alfabet['9'] = 44;
#pragma endregion
    int e, n, i = 0;
    char ch;
    char* line = new char[50];    


    ifstream mess("lab2/RSA_mess.txt");
    ifstream open("lab2/RSA_open.txt");
    ofstream encrypt("lab2/RSA_encrypt.txt");

    if (!mess || !open || !encrypt)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    open.getline(line, 50);
    e = atoi(line);
    open.getline(line, 50);
    n = atoi(line);
    
    cout << " Open keys "<< e << " " << n << endl;

    mess.seekg(0, ios_base::end);
    int* encryptMess = new int[mess.tellg()];
    mess.seekg(0, ios_base::beg);
    
    while (mess.get(ch)) {
        ch = toupper(ch);
        encryptMess[i] = codeLetter(e, n, alfabet[ch]);
        cout << " " << ch << " -> " << encryptMess[i] << endl;
        encrypt << encryptMess[i] << endl;
        i++;
    }

    mess.close();
    open.close();
    encrypt.close();
    delete[](encryptMess);
    return true;
}

bool decrypt() {
#pragma region init
    decodeMap alfabet;
    alfabet[1] = '�';
    alfabet[2] = '�';
    alfabet[3] = '�';
    alfabet[4] = '�';
    alfabet[5] = '�';
    alfabet[6] = '�';
    alfabet[7] = '�';
    alfabet[8] = '�';
    alfabet[9] = '�';
    alfabet[10] = '�';
    alfabet[11] = '�';
    alfabet[12] = '�';
    alfabet[13] = '�';
    alfabet[14] = '�';
    alfabet[15] = '�';
    alfabet[16] = '�';
    alfabet[17] = '�';
    alfabet[18] = '�';
    alfabet[19] = '�';
    alfabet[20] = '�';
    alfabet[21] = '�';
    alfabet[22] = '�';
    alfabet[23] = '�';
    alfabet[24] = '�';
    alfabet[25] = '�';
    alfabet[26] = '�';
    alfabet[27] = '�';
    alfabet[28] = '�';
    alfabet[29] = '�';
    alfabet[30] = '�';
    alfabet[31] = '�';
    alfabet[32] = '�';
    alfabet[33] = '�';
    alfabet[34] = ' ';
    alfabet[35] = '0';
    alfabet[36] = '1';
    alfabet[37] = '2';
    alfabet[38] = '3';
    alfabet[39] = '4';
    alfabet[40] = '5';
    alfabet[41] = '6';
    alfabet[42] = '7';
    alfabet[43] = '8';
    alfabet[44] = '9';
#pragma endregion
    int d, n, i = 0, let = 0;
    char ch;
    char* line = new char[50];

    ifstream close("lab2/RSA_close.txt");
    ifstream encrypt("lab2/RSA_encrypt.txt");

    if (!close || !encrypt)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    close.getline(line, 50);
    d = atoi(line);
    close.getline(line, 50);
    n = atoi(line);

    encrypt.seekg(0, ios_base::end);
    int* decryptMess = new int[encrypt.tellg()];
    encrypt.seekg(0, ios_base::beg);

    while (encrypt.getline(line, 50)) {
        let = atoi(line);
        decryptMess[i] = codeLetter(d, n, let);
        cout << decryptMess[i] << endl;
        cout << " " << let << " -> " << alfabet[decryptMess[i]] << endl;        
        i++;
    }

    for (int i = 0; i < encrypt.tellg(); i++) {
        cout << alfabet[decryptMess[i]];
    }
    cout << endl;

    close.close();
    encrypt.close();
    delete[](decryptMess);
    return true;
}

bool lab2() {
    setlocale(LC_ALL, "rus");
    int choose;
    bool flag;
    

    while (true) {
        flag = true;


        cout << "\n �������� ��������" << endl;
        cout << " 1. �������� ���� ������" << endl;
        cout << " 2. �����������" << endl;
        cout << " 3. ������������" << endl;
        cout << " 4. �����" << endl << endl;

        while (flag)
        {
            cout << " ������� �� ����: ";
            cin >> choose;

            switch (choose)
            {
            case 1: {
                if (!generateKey())
                    return false;
                flag = false;
                break;
            }
            case 2: {
                if (!encrypt())
                    return false;
                flag = false;
                break;
            }
            case 3: {
                if (!decrypt())
                    return false;
                flag = false;
                break;
            }
            case 4: {
                return true;
            }
            default:
                cout << " ������ �����, ��������� �������" << endl;
                break;
            }
        }
    }
}