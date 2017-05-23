#include <iostream>
#include <memory>
#include <utility>

#include "demo/vector.h"
#include "demo/verbose.h"

int main() {

    using std::make_unique;
    using std::move;
    using std::unique_ptr;

    using Demo::vector_fixed;
    using Demo::verbose_copy;

    vector_fixed<unique_ptr<verbose_copy>> vec{5};
    unique_ptr<verbose_copy> x = make_unique<verbose_copy>(3);
    unique_ptr<verbose_copy> y = make_unique<verbose_copy>(4);
    unique_ptr<verbose_copy> z = make_unique<verbose_copy>(5);
    vec.push_back(move(x));
    vec.push_back(move(y));
}

