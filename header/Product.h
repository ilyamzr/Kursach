#ifndef PRODUCTCLASS_H
#define PRODUCTCLASS_H

#include <string>
#include <fstream>
#include <iostream>
#include <string_view>
#include <vector>
#include <QString>
#include <random>

class Product {
    friend std::vector<std::string> searchForMatches(const QString &input);
    friend void createJsonOutput(const std::string& login, const std::vector<Product>& products);
    friend QString updateProductInfo(int index, const std::vector<Product>& products);

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
    static int getID(Product const &product)
    {
        return product.id;
    }
    [[nodiscard]] float getPrice() const
    {
        return price;
    }
    static std::string getOwner(Product const &product)
    {
        return product.owner;
    }
    static int getStatus(Product const &product){
        return product.forSale;
    }
    static Product changeStatus(Product &product){
        if (product.forSale == 0) product.forSale = 1;
        else if(product.forSale == 1) product.forSale = 0;
        return product;
    }
    static Product changeOwner(Product& product,const std::string& login){
        product.owner = login;
        return product;
    }
    static void addProductToCart(const std::string& login, int ID);
    static void deleteProduct(int ID);
    static void updateProductsInfo(const std::vector<Product>& products);
    static std::vector<Product> getMyProducts(const std::string& login);
    static std::vector<Product> categoriesSort(int categoryCheck, int subcategoryCheck, const std::string& login);
    static Product getProductByName(const std::string& name);
    static std::vector<Product> getProductsByName(const std::string& filename, const std::vector<std::string>& names);
    static Product getProductByID(int name);
    static std::vector<Product> getAllProducts(int mode);
    static int generateID();
};

#endif

