#include <iostream>
#include <vector>
#include "interfaceFuncs.h"
#include "productClass.h"

std::string getWord(std::string &line);
template <typename T>
void symbToDigit(std::string line, T* num)
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
Product addProduct(std::string_view login);
void viewProducts(const std::string_view &login, const std::string &filename, int mode);
void updateProductsInfo(const std::vector<Product>& products, const std::string& filename);
void addProductFunc(const std::string_view& login, const std::string& filename);
void deleteProductFunc(const std::string_view& login, const std::string& filename);
void categoriesFunc(const std::string& filename);

