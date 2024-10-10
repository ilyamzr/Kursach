#include <iostream>
#include "../header/Product.h"

void sellerMode(const std::string& login, const std::string& filename);
void buyermode(const std::string &login, const std::string &filename);
void printCategories();
void printSubCategories(int category);
void printProductInfo(Product& product);

