#include <string>
#include <fstream>
#include <iostream>
#include <string_view>

class Product {
    friend void deleteProduct(const std::string& filename, int deleteNum);
private:
    std::string name;
    int category{};
    int subcategory{};
    float price{};
    std::string description;
    int id{};
    std::string sellerName;

public:
    Product(std::string_view n, int c, int sc, float p, std::string_view d, int ID, std::string_view login)
            : name(n), category(c), subcategory(sc), price(p), description(d), id(ID), sellerName(login) {}

    static Product readFromFile(std::string line);
    static void saveProductToFile(const Product& product, const std::string &filename);
};
