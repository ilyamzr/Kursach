#include <iostream>
#include "Product.h"
#include <vector>

#ifndef PROFILECLASS_H
#define PROFILECLASS_H

template <typename T>
class Profile {
    friend void buyProduct(const std::string_view& login, int ID);
    friend Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
    friend void deleteProfile(const std::string& filename, const std::string_view& login);
    friend void depositMoney(const std::string_view& login, const std::string& filename);
    friend bool checkLogin(const std::string& login);

private:
    std::string login;
    T balance{};
    int productsAmount{};
    std::vector<int> userProducts;
    std::string password;

public:
    Profile(std::string l, std::string p, T b, int pa, std::vector<int> up)
            : login(std::move(l)), balance(b), productsAmount(pa), userProducts(std::move(up)), password(std::move(p)) {}

    Profile() = default;

    void setPassword(const std::string_view& newPassword) {
        password = newPassword;
    }

    template <typename U>
    static U updateBalance(U amount, T profileBalance) {
        U balance = static_cast<T>(amount) + profileBalance;
        return balance;
    }

    virtual ~Profile() = default;

    static void saveProfileToFile(const Profile& profile, const std::string& filename);
    static Profile readProfileFromFile(std::string line);
    static std::vector<int> getProducts(const Profile& profile) {
        return profile.userProducts;
    }

};

#endif