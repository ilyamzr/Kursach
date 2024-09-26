#include <iostream>
#include <string>
#include <windows.h>
#include "interfaceFuncs.h"
#include "profileFuncs.h"

using namespace std;

int main() {
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);
    string login;
    string filename = "products.txt";
    int choice;

    while (choice != 3)
    {
        cout << "Выберите действие:\n" << "1) Войти\n2) Зарегестрироваться" << endl;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Введите логин";
            cin >> login;

            int usermode = 0;
            while (usermode != 3)
            {
                cout << "Я хочу войти как:\n1) Продавец\n2) Покупатель\n3) Завершить" << endl;
                cin >> usermode;
                if (usermode == 1) {
                    sellerMode(login, filename);
                }
                else if (usermode == 2) {
                    buyermode(login, filename);
                }
                else if (usermode != 3)
                    cout << "Неверный выбор" << endl;
            }
        }
        else if (choice == 2) {
            createNewProfile();
        }
        else if (choice != 3) cout << "Неверный выбор" << endl;
    }
    return 0;
}