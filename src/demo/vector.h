#ifndef DEMO_VECTOR_H
#define DEMO_VECTOR_H

#include <memory>

namespace Demo {

    template<typename Type, typename Allocator = std::allocator<Type>>
    class vector_fixed {

        public:

            typedef Allocator allocator_type;
            typedef typename Allocator::const_pointer const_pointer;
            typedef typename Allocator::const_reference const_reference;
            typedef typename Allocator::difference_type difference_type;
            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::reference reference;
            typedef typename Allocator::size_type size_type;
            typedef typename Allocator::value_type value_type;
    };
}

#endif // DEMO_VECTOR_H

