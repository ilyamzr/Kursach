#include <iostream>
#include <fstream>
#include "../header/interfaceFuncs.h"
#include "../header/Profile.h"
#include "../header/Product.h"
#include "../header/operationFuncs.h"
#include "../header/ProductContainer.h"

using namespace std;

auto addProfile()
{
    cout << "Введите логин: ";
    string login;
    _flushall();
    getline(cin, login);
    cout << "Введите пароль: ";
    string password;
    _flushall();
    getline(cin, password);
    Profile profile(login, password, 0.0f);
    return profile;
}

void createNewProfile()
{
    string filename = "profileData.txt";
    Profile profile = addProfile();
    Profile::saveProfileToFile(profile, filename);
}

void updateProfilesInfo(const vector<Profile>& profiles, const string& filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (const Profile& profile : profiles) {
            Profile::saveProfileToFile(profile, filename);
        }
        file.close();
    } else {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
}

void deleteProfile(const string& filename, const string_view& login) {
    ifstream file(filename);
    vector<Profile> profiles;
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file, line);
            Profile profile = Profile::readProfileFromFile(line);
            if (profile.login != login && !profile.login.empty()) {
                profiles.push_back(profile);
            }
        }
        file.close();
    }
    updateProfilesInfo(profiles, filename);
}

/*Product getProductByID(const string& filename, int ID) {
    ifstream file(filename);
    string line;
    while (std::getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (product.id == ID) {
            return product;
        }
    }
    file.close();
    throw out_of_range("Товар с указанным идентификатором не найден.");
}*/

Product getProductByName(const string& filename, string name) {
    ifstream file(filename);
    string line;
    while (std::getline(file, line)) {
        Product product = Product::readFromFile(line);
        if (product.name == name) {
            return product;
        }
    }
    file.close();
    throw out_of_range("Товар с указанным идентификатором не найден.");
}

vector<Product> getProductsByName(const string& filename, vector<string> names) {
    ifstream file(filename);
    string line;
    vector<Product> products;
    while (std::getline(file, line)) {
        Product product = Product::readFromFile(line);
        for (int i = 0; i < names.size();i++)
        {
            if (product.name == names[i]) {
                products.push_back(getProductByName(filename,names[i]));
            }
        }
    }
    file.close();
    return products;
}

bool checkLogin(const string& login)
{
    ifstream file("ProfileData.txt");
    string line;
    string errorLine = "Пользователь с таким логином не найден";
    while (getline(file, line)) {
        Profile profile = Profile::readProfileFromFile(line);
        if (profile.login == login) {
            return true;
        }
    }
    throw errorLine;
}

void checkPassword(const string& login, const string& password)
{
    ifstream file("ProfileData.txt");
    string line;
    string errorLine = "Пароль неверный";
    while (getline(file, line)) {
        Profile profile = Profile::readProfileFromFile(line);
        if (profile.login == login) {
            if (profile.password == password)
            {
                break;
            }
            else
            {
                throw errorLine;
            }
        }
    }
}

Profile getProfileByLogin(const string& filename, const string_view& login) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Profile profile = Profile::readProfileFromFile(line);
        if (profile.login == login) {
            return profile;
        }
    }

    file.close();
    throw out_of_range("Профиль с указанным логином не найден.");
}

void buyProduct(const string_view& login, int ID)
{
    string productFilename = "products.txt";
    string profileFilename = "profileData.txt";
    Product product = ProductContainer::getProductByID(ID);
    Profile profile = getProfileByLogin(profileFilename, login);
    if (profile.balance < product.price)
    {
        cout << "Недостаточно денег на балансе" << endl;
    }
    else
    {
        Profile sellerProfile = getProfileByLogin(profileFilename, product.owner);
        cout << "Логин: " << sellerProfile.login << endl;
        sellerProfile.balance += product.price;
        product.owner = login;
        product.forSale = 0;
        cout << "Продукт: " << product.name << endl;
        deleteProduct(productFilename, product.id);
        Product::saveProductToFile(product, productFilename);
        profile.balance -= product.price;
        deleteProfile(profileFilename, login);
        deleteProfile(profileFilename, sellerProfile.login);
        Profile::saveProfileToFile(profile, profileFilename);
        Profile::saveProfileToFile(sellerProfile, profileFilename);
    }
}

void depositMoney(const string_view& login, const string& filename, float sum)
{
    Profile profile = getProfileByLogin(filename, login);
    profile.balance = Profile::updateBalance(sum,profile.balance);
    deleteProfile(filename, login);
    Profile::saveProfileToFile(profile, filename);
}