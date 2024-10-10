#include <iostream>
#include <fstream>
#include "../header/interfaceFuncs.h"
#include "../header/Profile.h"
#include "../header/operationFuncs.h"

using namespace std;

Profile addProfile()
{
    cout << "Введите логин: ";
    string login;
    _flushall();
    getline(cin,login);
    cout << "Введите пароль: ";
    string password;
    _flushall();
    getline(cin,password);
    vector<int> userProducts;
    Profile profile(login,password,0,0,userProducts);
    return profile;
}

void createNewProfile()
{
    string filename = "profileData.txt";
    Profile profile = addProfile();
    Profile::saveProfileToFile(profile,filename);
}

void updateProfilesInfo(const vector<Profile>& profiles, const string& filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (const Profile& profile : profiles) {
            Profile::saveProfileToFile(profile,filename);
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
            getline(file,line);
            if (!line.empty())
            {
                Profile profile = Profile::readProfileFromFile(line);
                if (profile != login) {
                    profiles.push_back(profile);
                }
            }
        }
        file.close();
    }
    updateProfilesInfo(profiles, filename);
}

Product getProductByID(const string& filename,int ID)
{
    ifstream file(filename);
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file,line);
            if (!line.empty())
            {
                Product product = Product::readFromFile(line);
                if (product.id == ID) {
                    return product;
                }
            }
        }
        file.close();
    }
}

Profile getProfileByLogin(const string& filename, const string_view& login)
{
    ifstream file(filename);
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file,line);
            if (!line.empty())
            {
                Profile profile = Profile::readProfileFromFile(line);
                if (profile == login) {
                    file.close();
                    return profile;
                }
            }
        }
        file.close();
    }
}

void buyProduct(const string_view& login, int ID)
{
    string productFilename = "products.txt";
    string profileFilename = "profileData.txt";
    Product product = getProductByID(productFilename,ID);
    Profile profile = getProfileByLogin(profileFilename,login);
    if (profile.balance < product.price)
    {
        cout << "Недостаточно денег на балансе" << endl;
    }
    else
    {
        Profile sellerProfile = getProfileByLogin(profileFilename,product.owner);
        sellerProfile = sellerProfile + product;
        product.owner = login;
        product.forSale = 0;
        deleteProduct(productFilename,product.id);
        Product::saveProductToFile(product, productFilename);
        profile = profile - product;
        profile.productsAmount++;
        profile.userProducts.push_back(product.id);
        deleteProfile(profileFilename,login);
        deleteProfile(profileFilename,sellerProfile.login);
        Profile::saveProfileToFile(profile,profileFilename);
        Profile::saveProfileToFile(sellerProfile,profileFilename);
    }
}

void buyProductFunc(const string_view& login)
{
    viewProducts(login,"products.txt",2);
    int choice;
    cout << "Выберите продукт из каталога" << endl;
    cin >> choice;
    int ID = getID(choice,login,2);
    buyProduct(login,ID);
}

void depositMoney(const string_view& login, const string& filename)
{
    cout << "Выберите сумму взноса" << endl;
    float sum;
    cin >> sum;
    Profile profile = getProfileByLogin(filename,login);
    profile.balance += sum;
    deleteProfile(filename,login);
    Profile::saveProfileToFile(profile,filename);
}

void checkProfileInfo(Profile& profile)
{
    cout << "Логин: " << profile.login << endl;
    cout << "<Баланс>: " << profile.balance << "$" << endl;
    cout << "Количество товаров: " << profile.productsAmount << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < profile.productsAmount; i++)
    {
        Product product = getProductByID("products.txt",profile.userProducts[i]);
        cout << i + 1 << ")" << endl;
        printProductInfo(product);
    }
}