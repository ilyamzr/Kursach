#include <iostream>
#include <string>
#include "fstream"
#include <vector>
#include <random>
#include "interfaceFuncs.h"
#include "operationFuncs.h"

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
        cout << "Не удалось открыть файл: " << filename << endl;
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
            if (count != deleteNum && !product.name.empty()) {
                products.push_back(product);
            }
            count++;
        }
        file.close();
    }
    updateProductsInfo(products, filename);
}

void categoriesSort(const string& filename, const int category, const int subcategory)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }
    string line;
    string word;
    int flag = 0;
    int i = 0;
    while (getline(file, line)) {
        getWord(line);
        string linecopy = line;
        getWord(line);
        word = getWord(line);
        int check;
        symbToDigit(word,&check);
        if (check == category) {
            word = getWord(line);
            symbToDigit(word,&check);
            if (check == subcategory)
            {
                i++;
                cout << "\n" << i << ")";
                printProductInfo(linecopy);
                flag = 1;
            }
        }
    }
    if (flag == 0) cout << "Таких товаров нет =(" << endl;
}

void addProductFunc(const string_view& login, const string& filename)
{
    Product newProduct = addProduct(login);
    Product::saveProductToFile(newProduct, filename);
}

void deleteProductFunc(const string_view& login, const string& filename)
{
    viewProducts(login,filename,1);
    cout << "Выберите товар, который хотите удалить";
    int deletedNum;
    cin >> deletedNum;
    deleteProduct(filename,deletedNum);
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