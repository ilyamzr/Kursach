#include "../header/Profile.h"
#include "../header/operationFuncs.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void Profile::saveProfileToFile(const Profile& profile, const std::string &filename) {
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << profile.login << "/" << profile.password << "/" << profile.balance << "/" << profile.productsAmount << "/";
        for (int i = 0; i < profile.productsAmount;i++)
        {
            file << profile.userProducts[i] << "/";
        }
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
    float b = stof(word);
    word = getWord(line);
    int pa;
    istringstream(word) >> pa;
    vector <int> up(pa);
    for (int i = 0; i < pa; i++)
    {
        word = getWord(line);
        istringstream(word) >> up[i];
    }
    return {l,p,b,pa,up};
}