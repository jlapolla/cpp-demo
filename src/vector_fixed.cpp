#include <iostream>

#include "demo/vector.h"
#include "demo/verbose.h"

int main() {

    using Demo::vector_fixed;
    using Demo::verbose_copy;

    verbose_copy x{3};
    std::cout << x.value() << std::endl;
}

