#include <iostream>

#include "demo/vector.h"
#include "demo/verbose.h"

int main() {

    using Demo::vector_fixed;
    using Demo::verbose_copy;

    vector_fixed<verbose_copy> vec{5};
    vec.push_back(verbose_copy{3});
}

