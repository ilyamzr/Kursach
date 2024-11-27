#ifndef PRODUCTCLASS_H
#define PRODUCTCLASS_H

#include <string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
#include <QString>

class Product {
    friend void deleteProduct(const std::string& filename, int deleteNum);
    friend int getID(int deletedNum, const std::string_view& login, int mode);
    friend void buyProduct(const std::string_view& login, int ID);
    friend void viewProducts(const std::string_view &login, const std::string &filename, int mode);
    friend std::vector<Product> categoriesSort(const std::string& filename, int category, int subcategory);
    friend QString updateProductInfo(int index, const std::vector<Product>& products);
    friend QString searchForMatches(const QString &input);
    friend Product getProductByName(const std::string& filename, std::string name);
    friend void createJsonOutput(const std::string& login,const Product& product);

private:
    std::string name;
    int category{};
    int subcategory{};
    float price{};
    std::string description;
    int id{};
    std::string owner;
    int forSale = 1;

public:
    Product(std::string_view n, int c, int sc, float p, std::string_view d, int ID, std::string_view login)
            : name(n), category(c), subcategory(sc), price(p), description(d), id(ID), owner(login) {}

    Product();

    virtual ~Product() = default;
    static Product readFromFile(std::string line);
    static void saveProductToFile(const Product& product, const std::string &filename);
    static void printProductInfo(Product& product);
    static int getID(Product const &product)
    {
        return product.id;
    }
    static std::string getProductCategory(int category);
    static std::string getProductSubCategory(int subcategory,int category);
    virtual void printError();
};

#endif

