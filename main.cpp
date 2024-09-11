#include <iostream>
#include "fstream"
#include <windows.h>
#include <array>
#include <vector>

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
template <typename T>
void symbToDigit(string line, T* num)
{
    int i = 0;
    *num = 0;
    while (line[i])
    {
        int temp = line[i] - '0';
        *num += static_cast<T>(temp * (static_cast<int>(line.size()) - i));
        i++;
    }
}

class Product {
    friend void deleteProduct(const string& filename, int deleteNum);
private:
    string name;
    int category{};
    int subcategory{};
    float price{};
    string description;
    int id{};
    string sellerName;
public:
    Product(string_view n, int c, int sc, float p, string_view d, int ID, string_view login)

            : name(n), category(c), subcategory(sc), price(p), description(d), id(ID), sellerName(login){}

    static Product readFromFile(string line) {
        string sn = getWord(line);
        string n = getWord(line);
        int c;
        symbToDigit(getWord(line),&c);
        int sc;
        symbToDigit(getWord(line),&sc);
        float p;
        symbToDigit(getWord(line),&p);
        string d = getWord(line);
        int ID;
        symbToDigit(getWord(line),&ID);

        return {n,c,sc,p,d,ID,sn};
    }

    static void saveProductToFile(const Product& product, const string &filename) {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << product.sellerName << "/" << product.name << "/" << product.category << "/" << product.subcategory << "/" << product.price << "/" << product.description << "/" << product.id << endl;
            file.close();
            cout << "Данные о товаре успешно сохранены" << endl;
        }
    }
};


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

Product addProduct(string_view login)
{
    cout << "Введите название продукта: ";
    string name;
    _flushall();
    std:: getline(cin,name);
    printCategories();
    cout << "Выберите категорию продукта: ";
    int category;
    cin >> category;
    cout << "Выберите подкатегорию: " << endl;
    printSubCategories(category-1);
    int subcategory;
    cin >> subcategory;
    cout << "Установите цену продукта: ";
    float price;
    cin >> price;
    cout << "Создайте описание товара: ";
    string descriprion;
    _flushall();
    std::getline(cin,descriprion);
    int id = rand() % 999999 + 1;
    Product product(name,category,subcategory,price,descriprion,id,login);
    return product;
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

void viewProducts(const string &login, const string &filename, int mode)
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
        if (string currentSellerName = getWord(line); currentSellerName == login || mode == 0) {
            i++;
            cout << "\n" << i << ")";
            printProductInfo(line);
            flag = 1;
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
        cout << "Error opening file for writing." << endl;
    }
}

void deleteProduct(const string& filename, int deleteNum) {
    ifstream file(filename);
    vector<Product> products;
    int count = 1;
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file,line);
            Product product = Product::readFromFile(line);
            if (count != deleteNum) {
                products.push_back(product);
            }
            count++;
        }
        file.close();
    }
    updateProductsInfo(products, filename);
}

void sellerMode(const string& login, const string& filename)
{
    int choice;
    while (choice != 4 && choice != 5)
    {
        cout << "Выберите действие:\n1) Добавить товар\n2) Посмотреть мои товары\n3) Удалить товар\n4) Назад\n5) Завершить";
        cin >> choice;
        if (choice == 1)
        {
            Product newProduct = addProduct(login);
            Product::saveProductToFile(newProduct, filename);
        }
        else if (choice == 2)
        {
            viewProducts(login, filename,1);
        }
        else if (choice == 3)
        {
            viewProducts(login,filename,1);
            cout << "Выберите товар, который хотите удалить";
            int deletedNum;
            cin >> deletedNum;
            deleteProduct(filename,deletedNum);
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
        printCategories();
        int category;
        cin >> category;
        printSubCategories(category);
        viewProducts(login,filename,0);
    }
    else if (choice == 2)
    {
        viewProducts(login,filename,0);
    }
    else if (choice != 4) cout << "Неверный выбор" << endl;
}

int main() {
    system("chcp 65001");
    SetConsoleOutputCP(CP_UTF8);
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
