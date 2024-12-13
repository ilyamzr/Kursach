#include <iostream>
#include <string>
#include "fstream"
#include <vector>
#include <json/json.h>
#include "../header/Product.h"

using namespace std;

string getWord(string &line)
{
    string word;
    if (size_t pos = line.find('/'); pos != string::npos) {
        word = line.substr(0, pos);
        line = line.substr(pos + 1);
    }
    return word;
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


void createJsonOutput(const std::string& login, const std::vector<Product>& products)
{
    QString userFileName = QString::fromStdString(login) + ".json";
    Json::Value jsonData;

    std::ifstream in(userFileName.toStdString());
    if (in) {
        in >> jsonData;
        in.close();
    }

    for (const auto& product : products) {
        Json::Value jsonProduct;
        jsonProduct["name"] = product.name;
        jsonProduct["category"] = product.category;
        jsonProduct["subcategory"] = product.subcategory;
        jsonProduct["price"] = product.price;
        jsonProduct["ID"] = product.id;

        jsonData.append(jsonProduct);
    }

    std::ofstream out(userFileName.toStdString());
    out << jsonData;
    out.close();
}