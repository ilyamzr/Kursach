#include <iostream>
#include "../header/Product.h"
#include "../header/operationFuncs.h"

#ifndef UNTITLED51_PROFILECONTROL_H
#define UNTITLED51_PROFILECONTROL_H

class ProfileControl {
public:
    virtual void printError() = 0;

    static void addProductFunc(const std::string& login) {
      
    }

    static void deleteProductFunc(const std::string& login) {
        viewProducts(login, "products.txt", 1);
        std::cout << "Выберите товар, который хотите удалить";
        int deletedNum;
        std::cin >> deletedNum;
        int ID = getID(deletedNum, login, 1);
        ::deleteProduct("products.txt", ID);
    }

    virtual ~ProfileControl() = default;
};

#endif //UNTITLED51_PROFILECONTROL_H