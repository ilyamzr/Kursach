#include <iostream>
#include <string>
#include <array>
#include "operationFuncs.h"

using namespace std;

void sellerMode(const string& login, const string& filename)
{
    int choice = 0;
    while (choice != 4 && choice != 5)
    {
        cout << "Выберите действие:\n1) Добавить товар\n2) Посмотреть мои товары\n3) Удалить товар\n4) Назад\n5) Завершить";
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
    }
}

void buyermode(const string &login, const string &filename)
{
    cout << "Выберите действие:\n1) Категории \n2) Все товары \n3) Профиль \n4) Назад";
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        categoriesFunc(login,filename);
    }
    else if (choice == 2)
    {
        viewProducts(login,filename,0);
    }
    else if (choice != 4) cout << "Неверный выбор" << endl;
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

void printProductInfo(string &productInfo)
{
    string word = getWord(productInfo);
    cout << "Наименование товара: " << word << endl;
    word = getWord(productInfo);
    int num1;
    symbToDigit(word, &num1);
    cout << allCategories[num1-1][0] << "/";
    word = getWord(productInfo);
    int num2;
    symbToDigit(word, &num2);
    cout << allCategories[num1-1][num2] << endl;
    word = getWord(productInfo);
    cout << "Цена: " << word << "$" << endl;
    word = getWord(productInfo);
    cout << "Описание товара: " << word << endl;
    word = getWord(productInfo);
    cout << "Артикул: " << word << endl;
}