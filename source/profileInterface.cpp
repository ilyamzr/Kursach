#include <iostream>
#include <string>
#include "../header/operationFuncs.h"
#include "../header/profileFuncs.h"
#include "../header/ProductData.h"

using namespace std;

void profileFunc(const string& login)
{
    string filename = "profileData.txt";
    int choice = 0;
    while (choice != 3)
    {
        cout << "Выберите действие:\n1) Посмотреть информацию профиля\n2) Пополнить баланс \n3) Назад";
        cin >> choice;
        if (choice == 1)
        {
            Profile profile = getProfileByLogin(filename,login);
            ProductData productData;
            ProductData::displayProfileAndProducts(profile);
        }
        else if (choice == 2)
        {
            depositMoney(login,filename);
        }
        else if (choice != 3) cout << "Неверный выбор" << endl;
    }
}