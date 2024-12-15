#ifndef UNTITLED51_CART_H
#define UNTITLED51_CART_H

#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include "../header/operationFuncs.h"
#include <sstream>

class Cart {
private:
    std::string owner;
    int productsNum = 0;
    std::vector<int> products;
public:

    explicit Cart(std::string  owner) : owner(std::move(owner)){}
    explicit Cart(std::string  owner, int productsNum, std::vector<int> products) : owner(std::move(owner)),productsNum(productsNum),products(std::move(products)) {}

    Cart();

    static Cart addProduct(Cart cart,int product) {
        cart.productsNum++;

        cart.products.push_back(product);
        return cart;
    }

    static void removeProduct(int id, const std::string& login);
    static void removeCart(const std::string& login);

    int getNum()
    {
        return productsNum;
    }
    int getProduct(int i) {
        if (i < 0 || i >= productsNum) {
            throw std::out_of_range("Product index out of range");
        }
        return products[i];
    }

    static Cart getCart(const std::string& login);
    static void saveCartToFile(const Cart& cart, const std::string &filename);
    Cart readCartFromFile(std::string line);
    float totalCost(Cart cart);
    static bool buyCart(Cart &cart, const std::string& login);
};

#endif //UNTITLED51_CART_H
