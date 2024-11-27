//
// Created by ASUS on 27.11.2024.
//

#ifndef UNTITLED51_PRODUCTITERATOR_H
#define UNTITLED51_PRODUCTITERATOR_H

#include "../header/ProductContainer.h"

class ProductIterator {
public:
    explicit ProductIterator(ProductContainer const& container);

    [[nodiscard]] bool hasNext() const {
        return index < container.size();
    }
    Product next();
    [[nodiscard]] Product getProduct() const
    {
        Product product = container.getProduct(index);
        return product;
    }

private:
    const ProductContainer& container;
    int index = 0;
};

#endif //UNTITLED51_PRODUCTITERATOR_H
