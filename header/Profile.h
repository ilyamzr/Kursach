#include <iostream>
#include "Product.h"
#include <utility>
#include <vector>
#include <string_view>

#ifndef PROFILECLASS_H
#define PROFILECLASS_H

class Profile {
    friend void buyProduct(const std::string_view& login, int ID);
    friend Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
    friend void deleteProfile(const std::string& filename, const std::string_view& login);
    friend void depositMoney(const std::string_view& login, const std::string& filename);
private:
    std::string login;
    std::string password;
    float balance{};
    int productsAmount{};
    std::vector <int> userProducts;
public:
    Profile(std::string l,std::string p, float b, int pa, std::vector <int> up)
            : login(std::move(l)),password(std::move(p)),balance(b),productsAmount(pa),userProducts(std::move(up)){}

    Profile();

    friend Profile operator+(const Profile& profile,const Product& product) {
        Profile newProfile = profile;
        newProfile.balance += product.getPrice();
        return newProfile;
    }

    friend Profile operator - (const Profile& profile,const Product& product) {
        Profile newProfile = profile;
        newProfile.balance -= product.getPrice();
        return newProfile;
    }

    bool operator==(const std::string_view& value) const {
        return this->login == value;
    }

    static void saveProfileToFile(const Profile &profile, const std::string &filename);
    static void checkProfileInfo(Profile &profile);
    static Profile readProfileFromFile(std::string line);

    [[nodiscard]] static int getProductsAmount(Profile const& profile) {
        return profile.productsAmount;
    }

    [[nodiscard]] static const std::vector<int>& getUserProducts(Profile const& profile) {
        return profile.userProducts;
    }

};
#endif