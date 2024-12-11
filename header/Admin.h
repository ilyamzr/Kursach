#include <iostream>
#include "../header/Profile.h"
#include "../header/ProfileControl.h"
#include "../header/profileFuncs.h"

#ifndef UNTITLED51_ADMIN_H
#define UNTITLED51_ADMIN_H

class Admin : public Profile, public ProfileControl {
public:
    Admin(std::string l, std::string p, float b)
            : Profile(std::move(l), std::move(p), b) {}

    static void resetUserPassword() {
        std::string log;
        std::cout << "Введите логин пользователя, профиль которого хотите изменить:" << std::endl;
        std::cin >> log;
        if (checkLogin(log))
        {
            Profile profile = getProfileByLogin("ProductData.txt", log);
            std::string newPassword;
            std::cout << "Введите новый пароль:";
            std::cin >> newPassword;
            profile.setPassword(newPassword);
            ProfileControl::deleteProductFunc(log);
            saveProfileToFile(profile, "ProfileData.txt");
        }
    }

    static void adminFunc(const std::string& log) {
        int choice = 0;
        while (choice != 4) {
            std::cout << "Выберите действие:\n1) Изменить пароль\n2) Добавить продукт\n3) Удалить продукт\n4) Назад";
            std::cin >> choice;
            if (choice == 1) {
                Admin::resetUserPassword();
            } else if (choice == 2) {
                ProfileControl::addProductFunc(log);
            } else if (choice == 3) {
                ProfileControl::deleteProductFunc(log);
            } else if (choice != 4) {
                std::cout << "Неверный выбор" << std::endl;
            }
        }
    }

    void printError() override {
        std::cerr << "Логин не найден" << std::endl;
    }
};

#endif //UNTITLED51_ADMIN_H