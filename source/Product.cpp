#include "../header/operationFuncs.h"
//#include "../source/interfaceFuncs.cpp"
#include <iostream>
#include <sstream>
#include <array>


using namespace std;

Product Product::readFromFile(std::string line) {
    std::string o = getWord(line);
    std::string n = getWord(line);
    std::string word = getWord(line);
    int c;
    std::istringstream(word) >> c;
    word = getWord(line);
    int sc;
    std::istringstream(word) >> sc;
    word = getWord(line);
    float p = stof(word);
    std::string d = getWord(line);
    word = getWord(line);
    int ID = stoi(word);
    word = getWord(line);
    int fs;
    std::istringstream(word) >> fs;
    Product product(n,c,sc,p,d,ID,o);
    product.forSale = fs;
    return product;
}

void Product::saveProductToFile(const Product& product, const std::string &filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << product.owner << "/" << product.name << "/" << product.category << "/" << product.subcategory << "/" << product.price << "/" << product.description << "/" << product.id << "/" << product.forSale << "/" << std::endl;
        file.close();
    }
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

void Product::printError()
{
    cout << "Guest mode" << endl;
}

void Product::printProductInfo(Product& product)
{
    if (product.name != ":guest:")
    {
        cout << "Наименование товара: " << product.name << endl;
        cout << allCategories[product.category-1][0] << "/";
        cout << allCategories[product.category-1][product.subcategory] << endl;
        cout << "Цена: " << product.price << "$" << endl;
        cout << "Описание товара: " << product.description << endl;
        cout << "Артикул: " << product.id << endl;
    }
    else
    {
        product.printError();
    }
}

