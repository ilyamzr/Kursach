#include <iostream>
<<<<<<< HEAD
<<<<<<< HEAD
#include <windows.h>
=======
#include <string>
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
=======
#include <string>
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
#include "interfaceFuncs.h"
#include <QApplication>
#include <QWidget>

using namespace std;

int main(int argc, char *argv[]) {
    system("chcp 65001");
<<<<<<< HEAD
<<<<<<< HEAD
    SetConsoleOutputCP(CP_UTF8);

    QApplication app(argc, argv);
    QWidget window;
    setupUI(&window);
    window.show();

    return QApplication::exec();
}
=======
=======
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
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
<<<<<<< HEAD
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
=======
>>>>>>> 010c55f5ef3869b70f5dc6105b6a95c277507403
