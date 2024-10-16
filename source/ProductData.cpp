#include "../header/ProductData.h"

void ProductData::displayProfileAndProducts(Profile &profile) {
    checkProfileInfo(profile);
    int amount = getProductsAmount(profile);
    const std::vector<int>& products = getUserProducts(profile);
    for (int i = 0; i < amount; ++i) {
        Product product = getProductByID("products.txt", products[i]);
        printProductInfo(product);
    }
}
