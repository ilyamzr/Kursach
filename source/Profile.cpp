#include "../header/Profile.h"
#include "../header/operationFuncs.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void Profile::saveProfileToFile(const Profile& profile, const std::string &filename) {
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << profile.login << "/" << profile.password << "/" << profile.balance << "/";
        file << endl;
        file.close();
    }
}

Profile Profile::readProfileFromFile(std::string line) {
    string word = getWord(line);
    string l = word;
    word = getWord(line);
    string p = word;
    word = getWord(line);
    float b;
    stringstream ss(word);
    ss >> b;
    return {l, p, b};
}

void Profile::updateProfilesInfo(const vector<Profile>& profiles, const string& filename)
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

void Profile::deleteProfile(const string& filename, const string_view& loginCheck) {
    ifstream file(filename);
    vector<Profile> profiles;
    if (file.is_open()) {
        while (file.good()) {
            string line;
            getline(file, line);
            Profile profile = Profile::readProfileFromFile(line);
            if (profile.login != loginCheck && !profile.login.empty()) {
                profiles.push_back(profile);
            }
        }
        file.close();
    }
    updateProfilesInfo(profiles, filename);
}



Profile Profile::getProfileByLogin(const string& filename, const string_view& loginCheck) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Profile profile = Profile::readProfileFromFile(line);
        if (profile.login == loginCheck) {
            return profile;
        }
    }
    file.close();
    throw out_of_range("Профиль с указанным логином не найден.");
}

bool Profile::checkLogin(const string& login)
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

void Profile::checkPassword(const string& login, const string& password)
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

bool Profile::checkRegLogin(const string& login)
{
    ifstream file("ProfileData.txt");
    string line;
    string errorLine;

    if (login.empty())
    {
        errorLine = "Логин не может быть пустым";
        throw errorLine;
    }
    if (login.contains(' '))
    {
        errorLine = "Логин не должен содержать пробелов";
        throw errorLine;
    }
    if (login.length() < 4)
    {
        errorLine = "Логин должен содержать хотя бы 4 символа";
        throw errorLine;
    }

    while (getline(file, line)) {
        Profile profile = Profile::readProfileFromFile(line);
        if (profile.login == login) {
            errorLine = "Пользователь с таким логином уже существует";
            throw errorLine;
        }
    }
    return true;
}

void Profile::checkRegPassword(const std::string& password)
{
    string errorLine;
    if (password.length() < 8)
    {
        errorLine = "Пароль должен содержать хотя бы 8 символов";
        throw errorLine;
    }
    if (password.contains(' '))
    {
        errorLine = "Пароль не должен содержать пробелов";
        throw errorLine;
    }
}