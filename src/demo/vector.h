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

            reference operator[](size_type Pos);
            const_reference operator[](size_type Pos) const;
            vector_fixed & operator=(const vector_fixed & right);
            vector_fixed & operator=(vector_fixed && right);

            reference back();
            const_reference back() const;
            size_type capacity() const;
            bool empty() const;
            bool full() const;
            void pop_back();
            void push_back(const Type & Val);
            void push_back(Type && Val);
            size_type size() const;

        private:

            size_type sz;
            size_type cap;
            pointer arr;
            Allocator al;
    };
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) {

    return arr[Pos];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) const {

    return arr[Pos];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::back() {

    return arr[sz - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::back() const {

    return arr[sz - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::capacity() const {

    return cap;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::empty() const {

    return sz == 0;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::full() const {

    return sz == cap;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::pop_back() {

    al.destroy(arr + (sz - 1));
    --sz;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(const Type & Val) {

    al.construct(arr + sz, Val);
    ++sz;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(Type && Val) {

    al.construct(arr + sz, Val);
    ++sz;
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::size() const {

    return sz;
}

#endif // DEMO_VECTOR_H

