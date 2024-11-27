#include "../header/Product.h"
#include <vector>
#include <fstream>
#include <algorithm>

class ProductContainer {
public:
    explicit ProductContainer(const std::vector<Product>& initialProducts) : products(initialProducts) {}

    static void addProduct(const Product& product, std::vector<Product>& products);

    static Product getProductByID(int ID);

    static std::vector<Product> getAllProducts();

    [[nodiscard]] size_t size() const { return products.size(); }
    [[nodiscard]] const Product& getProduct(const size_t index) const { return products.at(index); }


private:
    std::vector<Product> products;
};