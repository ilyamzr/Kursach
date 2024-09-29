#include <iostream>
#include <string>
#include "interfaceFuncs.h"

using namespace std;

int main() {
    system("chcp 65001");
    string login;
    string filename = "products.txt";
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
    return 0;
}
