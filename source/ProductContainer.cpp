#include "../header/ProductContainer.h"

void ProductContainer::addProduct(const Product& product, std::vector<Product>& products)
{
    return products.push_back(product);
}

Product ProductContainer::getProductByID(int ID)
{
    std::ifstream file("products.txt");
    std::string line;
    while (std::getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (Product::getID(product) == ID) {
            return product;
        }
    }
    file.close();
    throw std::out_of_range("Товар с указанным идентификатором не найден.");
}

std::vector<Product> ProductContainer::getAllProducts()
{
    std::ifstream file("products.txt");
    if (!file.is_open()) {
        std::cout << "Не удалось открыть файл: " << std::endl;
    }
    std::string line;
    std::vector<Product> productsArr;
    while (getline(file, line)) {
        if (!line.empty())
        {
            Product product = Product::readFromFile(line);
            ProductContainer::addProduct(product,productsArr);
        }
    }
    file.close();
    return productsArr;
}
