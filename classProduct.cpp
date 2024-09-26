#include <iostream>
#include <fstream>
#include "operationFuncs.h"

using namespace std;

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
        }
    }
};