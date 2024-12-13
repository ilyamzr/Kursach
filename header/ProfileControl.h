#include <iostream>
#include "../header/Product.h"
#include "../header/Profile.h"

#ifndef UNTITLED51_PROFILECONTROL_H
#define UNTITLED51_PROFILECONTROL_H

class ProfileControl {
public:
    virtual void printError() = 0;

    static void addProductFunc(const std::string& login) {
      
    }

    static void deleteProductFunc(const std::string& login) {

    }

    virtual ~ProfileControl() = default;
};

#endif //UNTITLED51_PROFILECONTROL_H