#include <iostream>
#include <string>
#include "fstream"
#include <vector>
#include <random>
#include "../header/interfaceFuncs.h"

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

Product addProduct(string_view login)
{
    cout << "Введите название продукта: ";
    string name;
    _flushall();
    getline(cin,name);
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
    getline(cin,descriprion);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution dis(1, 999999);
    int id = dis(gen);
    Product product(name,category,subcategory,price,descriprion,id,login);
    return product;
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
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file,line);
            Product product = Product::readFromFile(line);
            if (product.id != ID) {
                products.push_back(product);
            }
        }
        file.close();
    }
    updateProductsInfo(products, filename);
}

vector<Product> categoriesSort(const string& filename,  int category,  int subcategory)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
    string line;
    string word;
    int flag = 0;
    int i = 0;
    vector<Product> products;
    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (product.category == category && product.subcategory == subcategory) {
            i++;
            cout << "\n" << i << ")";
            if (product.forSale != 0)
            {
                products.push_back(product);
                Product::printProductInfo(product);
            }
            flag = 1;
        }
    }
    if (flag == 0) cout << "Таких товаров нет =(" << endl;
    return products;
}

void addProductFunc(const string_view& login)
{
    Product newProduct = addProduct(login);
    Product::saveProductToFile(newProduct, "products.txt");
}

int getID(int deletedNum, const std::string_view &login, int mode) {
    ifstream file("products.txt");

    int ID = -1;
    int count = 0;
    string line;

    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if ((product.owner == login && mode == 1) || (product.owner != login && mode == 2)) {
            count++;
            if (count == deletedNum) {
                ID = product.id;
                break;
            }
        }
    }

    file.close();

    if (ID == -1) {
        throw out_of_range("Количество удаленных продуктов превышает количество доступных.");
    }

    return ID;
}

void deleteProductFunc(const string_view& login)
{
    viewProducts(login,"products.txt",1);
    cout << "Выберите товар, который хотите удалить";
    int deletedNum;
    cin >> deletedNum;
    int ID = getID(deletedNum,login,1);
    deleteProduct("products.txt",ID);
}

void categoriesFunc(const string& filename)
{
    printCategories();
    cout << "Выберите категорию" << endl;
    int category;
    cin >> category;
    printSubCategories(category-1);
    cout << "Выберите подкатегорию" << endl;
    int subcategory;
    cin >> subcategory;
    categoriesSort(filename,category,subcategory);
}