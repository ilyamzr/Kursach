#include "../header/operationFuncs.h"
#include <iostream>
#include <sstream>

Product Product::readFromFile(std::string line) {
    std::string o = getWord(line);
    std::string n = getWord(line);
    std::string word = getWord(line);
    int c;
    std::istringstream(word) >> c;
    word = getWord(line);
    int sc;
    std::istringstream(word) >> sc;
    word = getWord(line);
    float p = stof(word);
    std::string d = getWord(line);
    word = getWord(line);
    int ID = stoi(word);
    word = getWord(line);
    int fs;
    std::istringstream(word) >> fs;
    Product product(n,c,sc,p,d,ID,o);
    product.forSale = fs;
    return product;
}

void Product::saveProductToFile(const Product& product, const std::string &filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << product.owner << "/" << product.name << "/" << product.category << "/" << product.subcategory << "/" << product.price << "/" << product.description << "/" << product.id << "/" << product.forSale << "/" << std::endl;
        file.close();
    }
}
