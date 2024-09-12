#include <iostream>
#include <vector>
#include <string>
#include "interfaceFuncs.h"

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
    Product(std::string_view n, int c, int sc, float p, std::string_view d, int ID, std::string_view login);
    static Product readFromFile(std::string line);
    static void saveProductToFile(const Product& product, const std::string &filename);
};
std::string getWord(std::string &line);
template <typename T>
void symbToDigit(std::string line, T* num);
Product addProduct(std::string_view login);
void viewProducts(const std::string &login, const std::string &filename, int mode);
void updateProductsInfo(const std::vector<Product>& products, const std::string& filename);
void deleteProduct(const std::string& filename, int deleteNum);
void addProductFunc(const std::string& login, const std::string& filename);