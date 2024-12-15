#include "../header/operationFuncs.h"
#include "../header/Profile.h"
#include "../header/Cart.h"
#include <iostream>
#include <sstream>

using namespace std;

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
    float p;
    istringstream(word) >> p;
    std::string d = getWord(line);
    word = getWord(line);
    int ID;
    istringstream(word) >> ID;
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

vector<Product> Product::getMyProducts(const std::string& login){
    ifstream file("products.txt");

    string line;
    vector<Product> products;
    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (Product::getOwner(product) == login) {
            products.push_back(product);
        }
    }
    file.close();
    return products;
}

vector<Product> Product::getAllProducts(int mode){
    ifstream file("products.txt");
    string line;
    vector<Product> products;
    while (getline(file, line)) {
        Product product = Product::readFromFile(line);
        if ((Product::getStatus(product) != 0 && mode == 1) || mode == 0) products.push_back(product);
    }
    file.close();
    return products;
}

vector<Product> Product::categoriesSort(int categoryCheck,  int subcategoryCheck, const std::string& login)
{
    vector<Product> newProducts;
    vector<Product> products = getAllProducts(1);
    for (const auto& product : products) {
        if (product.category == categoryCheck && product.subcategory == subcategoryCheck && product.forSale != 0 && product.owner != login) {
            newProducts.push_back(product);
        }
    }
    return newProducts;
}

Product Product::getProductByName(const string& check) {
    vector<Product> products = getAllProducts(1);
    for (const auto& product : products) {
        if (product.name == check) {
            return product;
        }
    }
    throw out_of_range("Товар с указанным идентификатором не найден.");
}

vector<Product> Product::getProductsByName(const string& filename, const vector<string>& names) {
    ifstream file(filename);
    string line;
    vector<Product> products;
    while (std::getline(file, line)) {
        Product product = Product::readFromFile(line);
        for (const auto & nameCheck : names)
        {
            if (product.name == nameCheck) {
                products.push_back(getProductByName(nameCheck));
            }
        }
    }
    file.close();
    return products;
}

Product Product::getProductByID(int check) {
    vector<Product> products = getAllProducts(0);
    for (const auto& product : products) {
        if (product.id == check) {
            return product;
        }
    }
    throw out_of_range("Товар с указанным идентификатором не найден.");
}

void Product::updateProductsInfo(const vector<Product>& products)
{
    ofstream file("products.txt");
    if (file.is_open()) {
        for (const Product& product : products) {
            Product::saveProductToFile(product,"products.txt");
        }
        file.close();
    } else {
        cout << "Не удалось открыть файл: " << "products.txt" << endl;
    }
}

void Product::deleteProduct(int ID) {
    vector<Product> products = getAllProducts(0);
    vector<Product> newProducts;
    for (const auto& product : products) {
        if (product.id != ID && !product.name.empty()) {
            newProducts.push_back(product);
        }
    }
    updateProductsInfo(newProducts);
}

void Product::addProductToCart(const string& login, int ID)
{
    Product product = Product::getProductByID(ID);
    product.forSale = 0;
    deleteProduct(ID);
    saveProductToFile(product,"products.txt");
    Cart cart(login);
    if(Cart::getCart(login).getNum() != 0) {
        cart = Cart::getCart(login);
    }
    cart = Cart::addProduct(cart,ID);
    Cart::saveCartToFile(cart,"carts.txt");
}

int Product::generateID()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dis(1, 99999);
    std::vector<Product> products = getAllProducts(1);

    std::vector<int> existingIDs;
    for (const auto& product : products) {
        existingIDs.push_back(product.id);
    }

    int ID;
    bool unique;
    do {
        unique = true;
        ID = dis(gen);

        for (const int existingID : existingIDs) {
            if (existingID == ID) {
                unique = false;
                break;
            }
        }
    } while (!unique);

    return ID;
}

Product::Product() = default;
