#include <iostream>
#include <fstream>
#include "profileClass.h"

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
    Profile profile(login,password);
    return profile;
}

void createNewProfile()
{
    string filename = "profileData";
    ofstream file(filename);
    if (file.is_open()) {
        Profile profile = addProfile();
        Profile::saveProfileToFile(profile,filename);
        file.close();
    } else {
        cout << "Не удалось открыть файл: " << filename << endl;
    }
}

