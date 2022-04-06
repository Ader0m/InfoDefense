#include <iostream>
#include "labs.h"

using namespace std;

/*
int main() {
    setlocale(LC_ALL, "rus");
    int choose;


    while (true) {
        bool flag = true;


        cout << "\n Выберите лабораторную работу" << endl;
        cout << " 1. Статические свойства открытых текстов" << endl;
        cout << " 2. RSA шифрование" << endl;
        cout << " 3. Выход" << endl << endl;
        cout << " ";

        while (flag)
        {
            cout << "Команда на ввод: ";
            cin >> choose;

            switch (choose)
            {
            case 1: {
                if (!lab1())
                    return -1;
                system("cls");
                flag = false;
                break;
            }
            case 2: {
                if (!lab2())
                    return -1;
                system("cls");
                flag = false;
                break;
            }
            case 3: {
                return 0;
            }
            default:
                cout << " Ошибка ввода, повторите попытку" << endl;
                break;
            }
        }
    }
}
*/