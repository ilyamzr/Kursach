#include "../header/Profile.h"
#include "../header/operationFuncs.h"
#include "../header/profileFuncs.h"
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



