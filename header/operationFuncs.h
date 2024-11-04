#include <iostream>
#include <vector>
#include "interfaceFuncs.h"
#include "Product.h"

std::string getWord(std::string &line);
Product addProduct(std::string_view login);
int getID(int deletedNum, const std::string_view &login, int mode);
void deleteProduct(const std::string& filename, int ID);
void viewProducts(const std::string_view &login, const std::string &filename, int mode);
void updateProductsInfo(const std::vector<Product>& products, const std::string& filename);
void addProductFunc(const std::string_view& login);
void deleteProductFunc(const std::string_view& login);
void categoriesFunc(const std::string& filename);
std::vector<Product> categoriesSort(const std::string& filename, int category, int subcategory);

