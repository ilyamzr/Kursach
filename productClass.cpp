#include "operationFuncs.h"

Product Product::readFromFile(std::string line) {
    std::string sn = getWord(line);
    std::string n = getWord(line);
    int c;
    symbToDigit(getWord(line), &c);
    int sc;
    symbToDigit(getWord(line), &sc);
    float p;
    symbToDigit(getWord(line), &p);
    std::string d = getWord(line);
    int ID;
    symbToDigit(getWord(line), &ID);

    return {n, c, sc, p, d, ID, sn};
}

void Product::saveProductToFile(const Product& product, const std::string &filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << product.sellerName << "/" << product.name << "/" << product.category << "/" << product.subcategory << "/" << product.price << "/" << product.description << "/" << product.id << "/" << std::endl;
        file.close();
        std::cout << "Данные о товаре успешно сохранены" << std::endl;
    }
}
