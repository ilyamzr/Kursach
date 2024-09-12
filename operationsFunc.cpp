#include <iostream>
#include <string>
#include "fstream"
#include <vector>
#include <random>
#include "interfaceFuncs.h"

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
            file << product.sellerName << "/" << product.name << "/" << product.category << "/" << product.subcategory << "/" << product.price << "/" << product.description << "/" << product.id << "/" << endl;
            file.close();
            cout << "Данные о товаре успешно сохранены" << endl;
        }
    }
};

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
    uniform_int_distribution dis(1, 100);
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
        cout << "Ошибка открытия файла" << endl;
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
            if (Product product = Product::readFromFile(line); count != deleteNum && !product.name.empty()) {
                products.push_back(product);
            }
            count++;
        }
        file.close();
    }
    updateProductsInfo(products, filename);
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

void categoriesFunc(const string_view& login, const string& filename)
{
    printCategories();
    int category;
    cin >> category;
    printSubCategories(category);
    viewProducts(login,filename,0);
}