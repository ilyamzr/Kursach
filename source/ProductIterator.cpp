#include "../header/ProductIterator.h"

ProductIterator::ProductIterator(ProductContainer const &container) : container(container){}

Product ProductIterator::next() {
    Product product = container.getProduct(index);
    ++index;
    return product;
}

