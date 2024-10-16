#include "../header/Product.h"
#include "../header/Profile.h"
#include "../header/profileFuncs.h"

#ifndef UNTITLED43_PRODUCTDATA_H
#define UNTITLED43_PRODUCTDATA_H

class ProductData: public Product, public Profile
{
public:
    ProductData() = default;
    static void displayProfileAndProducts(Profile& profile);
    void printError() override
    {
        std::cout << "No Profile data" << std::endl;
    }
};

#endif //UNTITLED43_PRODUCTDATA_H
