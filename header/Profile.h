#include <iostream>
#include <vector>
#include <QString>

#ifndef PROFILECLASS_H
#define PROFILECLASS_H

class Profile {
    friend QString updateProfileInfo(const Profile& profile);
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

    void updateBalance(float newBalance) {
        balance += newBalance;
    }

    [[nodiscard]] float getBalance() const{
        return balance;
    }

    std::string getLogin(){
        return login;
    }

    virtual ~Profile() = default;

    static void saveProfileToFile(const Profile& profile, const std::string& filename);
    static Profile readProfileFromFile(std::string line);
    void updateProfilesInfo(const std::vector<Profile>& profiles, const std::string& filename);
    void deleteProfile(const std::string& filename, const std::string_view& login);
    Profile getProfileByLogin(const std::string& filename, const std::string_view& login);
    static bool checkLogin(const std::string& login);
    static void checkPassword(const std::string& login, const std::string& password);
    static bool checkRegLogin(const std::string& login);
    static void checkRegPassword(const std::string& password);
};

#endif