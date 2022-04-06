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

        cout << " Пара простых чисел " << p << " " << q << endl;

        n = p * q;
        euler = (p - 1) * (q - 1);
        
        while (true) {
            e = rand() % (n-1) % 100 + 1;           
            if (vzaimnoProstoe(e, euler))
                break;

            if (k == 1000000) {
                cout << " Ключи не созданы\n" << endl;
                break;
            }
            k++;
        }        
        if (k == 1000000)
            continue;

        cout << " Пара открытых ключей " << e << " " << n << endl;
        
        while (true) {
            d = (double)(k * euler + 1) / e;
            if (int(d) == d) {
                break;
            }
            if ((int)k == 1000000) {
                cout << " Ключи не созданы\n" << endl;
                break;
            }
            k++;
        }
        if ((int)k < 100000)          
            break;        
    }
    cout << " Пара закрытых ключей " << d << " " << n << endl;

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
    alfabet['А'] = 1;
    alfabet['Б'] = 2;
    alfabet['В'] = 3;
    alfabet['Г'] = 4;
    alfabet['Д'] = 5;
    alfabet['Е'] = 6;
    alfabet['Ё'] = 7;
    alfabet['Ж'] = 8;
    alfabet['З'] = 9;
    alfabet['И'] = 10;
    alfabet['Й'] = 11;
    alfabet['К'] = 12;
    alfabet['Л'] = 13;
    alfabet['М'] = 14;
    alfabet['Н'] = 15;
    alfabet['О'] = 16;
    alfabet['П'] = 17;
    alfabet['Р'] = 18;
    alfabet['С'] = 19;
    alfabet['Т'] = 20;
    alfabet['У'] = 21;
    alfabet['Ф'] = 22;
    alfabet['Х'] = 23;
    alfabet['Ц'] = 24;
    alfabet['Ч'] = 25;
    alfabet['Ш'] = 26;
    alfabet['Щ'] = 27;
    alfabet['Ъ'] = 28;
    alfabet['Ы'] = 29;
    alfabet['Ь'] = 30;
    alfabet['Э'] = 31;
    alfabet['Ю'] = 32;
    alfabet['Я'] = 33;
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
    alfabet[1] = 'А';
    alfabet[2] = 'Б';
    alfabet[3] = 'В';
    alfabet[4] = 'Г';
    alfabet[5] = 'Д';
    alfabet[6] = 'Е';
    alfabet[7] = 'Ё';
    alfabet[8] = 'Ж';
    alfabet[9] = 'З';
    alfabet[10] = 'И';
    alfabet[11] = 'Й';
    alfabet[12] = 'К';
    alfabet[13] = 'Л';
    alfabet[14] = 'М';
    alfabet[15] = 'Н';
    alfabet[16] = 'О';
    alfabet[17] = 'П';
    alfabet[18] = 'Р';
    alfabet[19] = 'С';
    alfabet[20] = 'Т';
    alfabet[21] = 'У';
    alfabet[22] = 'Ф';
    alfabet[23] = 'Х';
    alfabet[24] = 'Ц';
    alfabet[25] = 'Ч';
    alfabet[26] = 'Ш';
    alfabet[27] = 'Щ';
    alfabet[28] = 'Ъ';
    alfabet[29] = 'Ы';
    alfabet[30] = 'Ь';
    alfabet[31] = 'Э';
    alfabet[32] = 'Ю';
    alfabet[33] = 'Я';
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


        cout << "\n Выберите действие" << endl;
        cout << " 1. Создание пары ключей" << endl;
        cout << " 2. Зашифровать" << endl;
        cout << " 3. Расшифровать" << endl;
        cout << " 4. Выход" << endl << endl;

        while (flag)
        {
            cout << " Команда на ввод: ";
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
                cout << " Ошибка ввода, повторите попытку" << endl;
                break;
            }
        }
    }
}