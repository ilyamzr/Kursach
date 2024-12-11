#include <iostream>
#include "Product.h"
#include <vector>
#include <QString>

#ifndef PROFILECLASS_H
#define PROFILECLASS_H

class Profile {
    friend void buyProduct(const std::string_view& login, int ID);
    friend Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
    friend void deleteProfile(const std::string& filename, const std::string_view& login);
    friend void depositMoney(const std::string_view& login, const std::string& filename, float sum);
    friend QString updateProfileInfo(const Profile& product);
    friend bool checkLogin(const std::string& login);
    friend void checkPassword(const std::string& password,const std::string& login);

private:
    std::string login;
    float balance{};
    std::string password;

public:
    Profile(std::string l, std::string p, float b)
            : login(std::move(l)), balance(b), password(std::move(p)) {}

    Profile() = default;

    void setPassword(const std::string_view& newPassword) {
        password = newPassword;
    }

    template <typename U>
    static U updateBalance(U amount, float profileBalance) {
        U balance = static_cast<float>(amount) + profileBalance;
        return balance;
    }

    virtual ~Profile() = default;

    static void saveProfileToFile(const Profile& profile, const std::string& filename);
    static Profile readProfileFromFile(std::string line);
};

#endif