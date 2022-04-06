#include <iostream>
#include "labs.h"
#include <fstream>
#include <windows.h>

#define file1  "lab3/1.bmp"
#define file2  "lab3/2.bmp"

using namespace std;

BITMAPFILEHEADER bmfh;
BITMAPINFOHEADER bmih;

void hide_byte_into_pixel(RGBQUAD* pixel, uint8_t hide_byte)
{
    pixel->rgbBlue &= (0xFC);
    pixel->rgbBlue |= (hide_byte >> 6) & 0x3;
    pixel->rgbGreen &= (0xFC);
    pixel->rgbGreen |= (hide_byte >> 4) & 0x3;
    pixel->rgbRed &= (0xFC);
    pixel->rgbRed |= (hide_byte >> 2) & 0x3;
    pixel->rgbReserved &= (0xFC);
    pixel->rgbReserved |= (hide_byte) & 0x3;
}

char read_byte_into_pixel(RGBQUAD* pixel) {
    char ch = 0;


    ch = pixel->rgbBlue & 3;
    ch <<= 2;
    ch |= pixel->rgbGreen & 3;
    ch <<= 2;
    ch |= pixel->rgbRed & 3;
    ch <<= 2;
    ch |= pixel->rgbReserved & 3;
    ch <<= 2;

   
    return ch;
}

bool getBmpInfo(string namefile) {
    ifstream file(namefile, ios::binary);
    char* ch2;

    if (!file)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    //BITMAPFILEHEADER
    file.read((char*)&bmfh, sizeof(BITMAPFILEHEADER));
    //BITMAPINFOHEADER
    file.read((char*)&bmih, sizeof(BITMAPINFOHEADER));

    file.close();
}

bool encryptBMP(string str) {
    char ch;
    int countPixel = 0;


    ifstream img(file1, ios::binary);
    ofstream img2(file2, ios::binary);
    if (!img)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }
    if (!img2)
    {
        cout << "File111 don't open!" << endl;
        system("pause");
        return false;
    }

    img.seekg(0, ios_base::end);
    RGBQUAD* pixel = new RGBQUAD[(unsigned long int) img.tellg() - bmfh.bfOffBits];
    img.seekg(0, ios_base::beg);
    img.seekg(bmfh.bfOffBits);

    while (img.read((char*)&pixel[countPixel], sizeof(RGBQUAD))) {
        if(countPixel< str.size())
            hide_byte_into_pixel(&pixel[countPixel], str[countPixel]);
        if(countPixel == str.size())
            hide_byte_into_pixel(&pixel[countPixel], 0xFF);
        countPixel++;
    }
    
    cout << (int)pixel[0].rgbBlue << " " <<  (int)pixel[0].rgbGreen << " " << (int) pixel[0].rgbRed << endl;
    cout << countPixel*3;
    
    img.close();
    img2.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));
    img2.write((char*)&bmih, sizeof(BITMAPINFOHEADER));

    for (int i = 0; i < countPixel; i++) {
        img2.write((char*)&pixel[i], sizeof(RGBQUAD));
    }

    img2.close();
}

bool decryptBMP() {
    int countPixel = 0;


    ifstream img(file2, ios::binary);
    if (!img)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    img.seekg(0, ios_base::end);
    int count = (unsigned long int) img.tellg() - bmfh.bfOffBits;
    RGBQUAD* pixel = new RGBQUAD[count];
    char* ch = new char[count];
    img.seekg(0, ios_base::beg);
    img.seekg(bmfh.bfOffBits);

    while (img.read((char*)&pixel[countPixel], sizeof(RGBQUAD))) {
        ch[countPixel] = read_byte_into_pixel(&pixel[countPixel]);
        countPixel++;
        if (0xFF == ch[countPixel-1])
            break;
    }

    img.close();

    ofstream file("lab3/output.txt");
    if (!file)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }
    for (int i = 0; i < countPixel; i++)
        file << ch[i];
}

bool copyBMP() {
    char ch;
    int countPixel = 0;
    bool flag = true;
    

    ifstream img(file1, ios::binary);
    ofstream img2(file2, ios::binary);
    if (!img)
    {
        cout << "File don't open!" << endl;
        system("pause");
        return false;
    }

    if (!img2)
    {
        cout << "File111 don't open!" << endl;
        system("pause");
        return false;
    }

    img.seekg(0, ios_base::end);
    RGBQUAD* pixel = new RGBQUAD[(unsigned long int) img.tellg() - bmfh.bfOffBits];
    img.seekg(0, ios_base::beg);
    img.seekg(bmfh.bfOffBits);

    while (img.read((char*)&pixel[countPixel], sizeof(RGBQUAD))) {
        countPixel++;
    }
    img.close(); 
    
    img2.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));
    img2.write((char*)&bmih, sizeof(BITMAPINFOHEADER));

    for (int i = 0; i < countPixel; i++) {
        img2.write((char*)&pixel[i], sizeof(RGBQUAD));
    }

    img2.close();
    
} // копировование

void abv() { 
    char ch;
    char ch2;
    int num = 1;
    ifstream img(file1, ios::binary);
    ifstream img2(file2, ios::binary);

    while (img.get(ch)) {        
        img2.get(ch2);
        if (ch != ch2) {
            cout << " Ошибка копирования" << endl;
            cout << " Исходник " << ch;
            cout << " Копия " << ch2 << " Номер байта " << num << endl;
            break;
        }       
        num++;
    }  
    cout << "Успешное копирование" << endl;
} // правильность копирования

int main() {
    setlocale(LC_ALL, "rus");
    int choose; 
    string str = "abcd";
    
    getBmpInfo(file1);
    
    while (true) {
        bool flag = true;
        

        cout << "\n Выберите действие" << endl;
        cout << " 1. Создать сообщение" << endl;
        cout << " 2. Зашифровать" << endl;
        cout << " 3. Расшифровать" << endl;
        cout << " 4. Копирование" << endl;
        cout << " 5. Выход" << endl;
        cout << " 6. Балуемся" << endl << endl;

        while (flag)
        {
            cout << " Команда на ввод: ";
            cin >> choose;

            switch (choose)
            {
            case 1: {
                
                
                flag = false;
                break;
            }
            case 2: {
                encryptBMP(str);
                
                flag = false;
                break;
            }
            case 3: {                                            
                decryptBMP();
               
                break;
            }
            case 4: {
                copyBMP();
                abv();
                break;
            }
            case 5: {
                return 0;
            }
            case 6: {
                abv();

                flag = false;
                return 0;
            }
            default:
                cout << " Ошибка ввода, повторите попытку" << endl;
                break;
            }
        }
    }
}
