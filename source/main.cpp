#include <iostream>
#include <string>
#include "../header/interfaceFuncs.h"
#include "../header/profileFuncs.h"
using namespace std;

int main() {
    system("chcp 65001");
    string login = ":guest:";
    string filename = "products.txt";
    int choice = 0;

    while (true)
    {
        cout << "Выберите действие:\n" << "1) Войти\n2) Зарегестрироваться\n3) Войти как гость" << endl;
        cin >> choice;

        if (choice == 1 || choice == 3)
        {
            if (choice != 3)
            {
                cout << "Введите логин";
                cin >> login;
            }
            int usermode = 0;
            while (usermode != 3)
            {
                usermode = guestMode(choice,login,filename,usermode);
            }
        }
        else if (choice == 2) {
            createNewProfile();
        }
        else if (choice == 3) break;
        else cout << "Неверный выбор" << endl;
    }
    return 0;
}