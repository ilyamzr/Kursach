#include <iostream>
#include <string>
#include <array>
#include "../header/operationFuncs.h"
#include "../header/profileFuncs.h"
#include "../header/profileInterface.h"

using namespace std;

void sellerMode(const string& login, const string& filename)
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "Выберите действие:\n1) Добавить товар\n2) Посмотреть мои товары\n3) Удалить товар\n4) Назад";
        cin >> choice;
        if (choice == 1)
        {
            addProductFunc(login,filename);
        }
        else if (choice == 2)
        {
            viewProducts(login, filename,1);
        }
        else if (choice == 3)
        {
            deleteProductFunc(login,filename);
        }
        else if (choice != 4) cout << "Неверный выбор" << endl;
    }
}

void buyermode(const string &login, const string &filename)
{
    int choice = 0;
    while (choice != 4)
    {
        cout << "Выберите действие:\n1) Категории \n2) Все товары \n3) Купить \n4) Профиль \n5) Назад";
        cin >> choice;
        if (choice == 1)
        {
            categoriesFunc(filename);
        }
        else if (choice == 2)
        {
            viewProducts(login,filename,0);
        }
        else if (choice == 3)
        {
            buyProductFunc(login);
        }
        else if (choice == 4)
        {
            profileFunc(login);
        }
        else if (choice != 5) cout << "Неверный выбор" << endl;
    }

}

int guestMode(int choice, const string& login, const string& filename, int usermode)
{
    if (choice != 3)
    {
        cout << "Я хочу войти как:\n1) Продавец\n2) Покупатель\n3) Завершить" << endl;
        cin >> usermode;
    }
    else usermode = 2;
    if (usermode == 1) {
        sellerMode(login, filename);
    }
    else if (usermode == 2) {
        buyermode(login, filename);
    }
    else if (usermode != 3)
        cout << "Неверный выбор" << endl;
    return usermode;
}

const std::array<std::array<std::string, 6>, 9> allCategories = {{
    {"Техника", "Смартфон", "Ноутбуки", "Телевизоры", "Бытовая техника", "Аудио и видео техника"},
    {"Спорт и активный отдых", "Спортивная одежда", "Спортивная обувь", "Тренажеры и фитнес-оборудование", "Туристическое снаряжение", "Велосипеды и аксессуары"},
    {"Мебель", "Мебель для гостиной", "Мебель для спальни", "Мебель для кухни", "Офисная мебель", "Детская мебель"},
    {"Дом", "Декор", "Освещение", "Текстиль", "Хранение", "Уборка"},
    {"Игрушки", "Конструкторы", "Мягкие игрушки", "Настольные игры", "Развивающие игрушки", "Электронные игрушки"},
    {"Мужчинам", "Одежда", "Обувь", "Аксессуары", "Парфюмерия", "Спортивные товары"},
    {"Женщинам", "Одежда", "Обувь", "Аксессуары", "Косметика", "Парфюмерия"},
    {"Детям", "Одежда", "Обувь", "Игрушки", "Учебные материалы", "Спортивные товары"},{"Продукты", "Фрукты и овощи", "Молочные продукты", "Мясо и рыба", "Бакалея", "Напитки" }
}};

void printCategories()
{
    for (int i = 0; i < 9; i++)
    {
        cout << i+1 << ") " << allCategories[i][0] << endl;
    }
}
void printSubCategories(int category)
{
    for (int i = 1; i < 6; i++)
    {
        cout << i << ") " << allCategories[category][i] << endl;
    }
}

