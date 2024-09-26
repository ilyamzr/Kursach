#include <iostream>
#include "productClass.h"
#include <utility>
#include <vector>
#include <string_view>

class Profile
{
private:
    std::string login;
    std::string password;
    float balance;
    std::vector <Product> userProducts;
public:
    Profile(std::string  l,std::string  p)
    : login(std::move(l)),password(std::move(p)),balance(0){}

    static void saveProfileToFile(Profile &profile, const std::string &filename);
};