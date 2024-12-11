#include <iostream>
#include <string>
#include "fstream"
#include <vector>
#include "../header/interfaceFuncs.h"
#include <json/json.h>

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

void viewProducts(const string_view &login, const string &filename, int mode)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }
    string line;
    int flag = 0;
    int i = 0;
    while (getline(file, line)) {
        if (!line.empty())
        {
            Product product = Product::readFromFile(line);
            if (((product.owner == login && mode == 1) || (product.owner != login && mode == 2) || mode == 0) && product.forSale != 0) {
                i++;
                cout << "\n" << i << ")";
                Product::printProductInfo(product);
                flag = 1;
            }
        }
    }
    if (flag == 0) cout << "У вас нету товаров =(" << endl;
    file.close();
}

void updateProductsInfo(const vector<Product>& products, const string& filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (const Product& product : products) {
            Product::saveProductToFile(product,filename);
        }
        file.close();
    } else {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
}

void deleteProduct(const string& filename, int ID) {
    ifstream file(filename);
    vector<Product> products;
    cout << "|" << ID << "|";
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file,line);
            Product product = Product::readFromFile(line);
            if (product.id != ID && !product.name.empty()) {
                products.push_back(product);
            }
        }
        file.close();
    }
    updateProductsInfo(products, filename);
}

vector<Product> getMyProducts(const std::string& login){
    ifstream file("products.txt");

    int ID = -1;
    int count = 0;
    string line;
    vector<Product> products;
    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (Product::getOwner(product) == login) {
            products.push_back(product);
        }
    }
    file.close();
    return products;
}

vector<Product> categoriesSort(const string& filename,  int category,  int subcategory, const std::string& login)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
    string line;
    string word;
    vector<Product> products;
    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (product.category == category && product.subcategory == subcategory && product.forSale != 0 && product.owner != login) {
            products.push_back(product);
        }
    }
    return products;
}


int getID(int deletedNum, const std::string_view &login, int mode) {
    ifstream file("products.txt");

    int ID = -1;
    int count = 0;
    string line;

    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if ((product.owner == login && mode == 1) || (product.owner != login && mode == 2)) {
            cout << "/" << product.id << "/" << endl;
            if (count == deletedNum) {
                ID = product.id;
                break;
            }
            count++;
        }
    }

    file.close();

    if (ID == -1) {
        throw out_of_range("Количество удаленных продуктов превышает количество доступных.");
    }

    return ID;
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