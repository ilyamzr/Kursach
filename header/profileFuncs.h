#include <iostream>
#include <vector>
#include "../header/Profile.h"

void createNewProfile();
void addProfile();
void buyProductFunc(const std::string_view& login);
Product getProductByID(const std::string& filename, int ID);
Product getProductByName(const std::string& filename, std::string name);
std::vector<Product> getProductsByName(const std::string& filename, std::vector<std::string> names);
void depositMoney(const std::string_view& login, const std::string& filename, float sum);
Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
void buyProduct(const std::string_view& login, int ID);
bool checkLogin(const std::string& login);
void checkPassword(const std::string& login, const std::string& password);