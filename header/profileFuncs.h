#include <iostream>
#include <vector>
#include "../header/Profile.h"

void createNewProfile();
void addProfile();
void buyProductFunc(const std::string_view& login);
Product getProductByID(const std::string& filename, int ID);
void depositMoney(const std::string_view& login, const std::string& filename, float sum);
Profile<float> getProfileByLogin(const std::string& filename, const std::string_view& login);
void buyProduct(const std::string_view& login, int ID);
bool checkLogin(const std::string& login);
