#include <iostream>
#include "profileClass.h"

using namespace std;

void Profile::saveProfileToFile(Profile& profile, const std::string &filename) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << profile.login << "/" << profile.password << "/" << profile.balance << "/" << std::endl;
        file.close();
        std::cout << "Данные о товаре успешно сохранены" << std::endl;
    }
}