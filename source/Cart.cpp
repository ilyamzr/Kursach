#include "../header/Cart.h"
#include "../header/Profile.h"


Cart Cart::getCart(const std::string& login) {
    std::ifstream file("carts.txt");
    std::string line;
    while (getline(file, line)) {
        Cart cart;
        cart = cart.readCartFromFile(line);
        if (cart.owner == login) {
            return cart;
        }
    }
    return {};
}

float Cart::totalCost(Cart cart)  {
    float total = 0;

    for (const auto& product : cart.products) {
        Product temp;
        temp = temp.getProductByID(product);
        total += temp.getPrice();
    }
    return total;
}

void Cart::saveCartToFile(const Cart& cart, const std::string &filename) {

    std::ofstream file(filename, std::ios::app);
    if(cart.productsNum != 0) removeCart(cart.owner);
    if (file.is_open()) {
        file << cart.owner << "/" << cart.productsNum << "/";
        for (int i = 0; i < cart.productsNum; i++)
        {
            file << cart.products[i] << "/";
        }
        file << std::endl;
        file.close();
    }
}

std::vector<Cart> getAllCarts(){
    std::ifstream file("carts.txt");
    std::string line;
    std::vector<Cart> carts;
    while (getline(file, line)) {
        Cart cart;
        cart = cart.readCartFromFile(line);
        carts.push_back(cart);
    }
    file.close();
    return carts;
}

Cart Cart::readCartFromFile(std::string line) {
    std::string o = getWord(line);
    std::string n = getWord(line);
    int num;
    std::vector <int> prods;
    std::istringstream(n) >> num;
    prods.resize(num);
    for (int i = 0; i < num; i++)
    {
        std::string temp = getWord(line);
        std::istringstream(temp) >> prods[i];
    }
    Cart cart(o,num,prods);
    return cart;
}

void Cart::removeProduct(int id, const std::string& login)
{
    removeCart(login);
    Product product;
    product = Product::getProductByID(id);
    product = Product::changeStatus(product);
    Product::deleteProduct(Product::getID(product));
    Product::saveProductToFile(product, "products.txt");
}

bool Cart::buyCart(Cart &cart, const std::string& login)
{
    Profile profile;
    profile = profile.getProfileByLogin("ProfileData.txt", login);
    if (profile.getBalance() >= cart.totalCost(cart))
    {
        for (int i = 0; i < cart.productsNum; i++)
        {
            Profile sellerProfile;
            Product product;
            product = Product::getProductByID(cart.getProduct(i));
            sellerProfile = sellerProfile.getProfileByLogin("ProfileData.txt", Product::getOwner(product));
            sellerProfile.updateBalance(product.getPrice());
            product = Product::changeOwner(product,login);
            Product::deleteProduct(Product::getID(product));
            Product::saveProductToFile(product, "products.txt");
            profile.updateBalance(-product.getPrice());
            profile.deleteProfile("ProfileData.txt", login);
            profile.deleteProfile("ProfileData.txt", sellerProfile.getLogin());
            Profile::saveProfileToFile(profile, "ProfileData.txt");
            Profile::saveProfileToFile(sellerProfile, "ProfileData.txt");
            removeCart(login);
        }
        return true;
    }
    else return false;
}

void Cart::removeCart(const std::string& login)
{
    std::vector<Cart> carts = getAllCarts();

    std::ofstream outFile("carts.txt", std::ios::trunc);
    outFile.close();

    for (const auto& cart : carts)
    {
        if (cart.owner != login)
        {
            Cart::saveCartToFile(cart, "carts.txt");
        }
    }
}

Cart::Cart() = default;
