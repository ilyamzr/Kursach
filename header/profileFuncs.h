#include <iostream>
#include <vector>
#include "../header/Profile.h"

void createNewProfile();
void addProfile();
void buyProduct(Product &product, const std::string_view& login);
void updateProductsInfo(const std::vector<Profile>& profiles, const std::string& filename);
void buyProductFunc(const std::string_view& login);
void depositMoney(const std::string_view& login, const std::string& filename);
Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
