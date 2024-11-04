#include "../header/Profile.h"
#include "../header/operationFuncs.h"
#include "../header/profileFuncs.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
void Profile<T>::saveProfileToFile(const Profile<T>& profile, const std::string &filename) {
    ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << profile.login << "/" << profile.password << "/" << profile.balance << "/" << profile.productsAmount << "/";
        for (int i = 0; i < profile.productsAmount; i++) {
            file << profile.userProducts[i] << "/";
        }
        file << endl;
        file.close();
    }
}

template <typename T>
Profile<T> Profile<T>::readProfileFromFile(std::string line) {
    string word = getWord(line);
    string l = word;
    word = getWord(line);
    string p = word;
    word = getWord(line);
    T b;
    stringstream ss(word);
    ss >> b;
    word = getWord(line);
    int pa;
    istringstream(word) >> pa;
    vector<int> up(pa);
    for (int i = 0; i < pa; i++) {
        word = getWord(line);
        istringstream(word) >> up[i];
    }
    return {l, p, b, pa, up};
}



template class Profile<float>;