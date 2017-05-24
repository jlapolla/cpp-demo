#ifndef DEMO_VECTOR_H
#define DEMO_VECTOR_H

#include <memory>
#include <new>
#include <utility>

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
            vector_fixed & operator=(const vector_fixed & Right);
            vector_fixed & operator=(vector_fixed && Right);

            explicit vector_fixed(size_type Count);
            ~vector_fixed();

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

            size_type my_size;
            size_type cap;
            pointer arr;
            Allocator al;

        // CLASS INVARIANT
        //
        // assert forall i: 0 <= i -> i < my_size -> is_valid_object(arr[i])
        // assert forall i: my_size <= i -> i < cap -> ~is_valid_object(arr[i])
        // assert forall i: 0 <= i -> i < cap -> is_allocated_space(arr + i)
        // assert 0 <= my_size
        // assert my_size <= cap
    };
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) {

    // assert 0 <= Pos
    // assert Pos < my_size

    return arr[Pos];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) const {

    // assert 0 <= Pos
    // assert Pos < my_size

    return arr[Pos];
}

template<typename Type, typename Allocator>
Demo::vector_fixed<Type, Allocator>::vector_fixed(Demo::vector_fixed<Type, Allocator>::size_type Count) {

    // assert 0 <= Count

    if (Count != 0) {

        // ->
        // assert 0 < Count

        arr = al.allocate(Count, nullptr);
        if (arr == nullptr) {

            throw std::bad_alloc();
        }
    }
    else {

        // ->
        // assert 0 = Count

        arr = nullptr;
    }

    my_size = static_cast<Demo::vector_fixed<Type, Allocator>::size_type>(0);
    cap = Count;

    // ->
    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(arr[i])
    // assert forall i: my_size <= i -> i < cap -> ~is_valid_object(arr[i])
    // assert forall i: 0 <= i -> i < cap -> is_allocated_space(arr + i)
    // assert 0 <= my_size
    // assert my_size <= cap
}

template<typename Type, typename Allocator>
Demo::vector_fixed<Type, Allocator>::~vector_fixed() {

    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(arr[i])
    // assert forall i: my_size <= i -> i < cap -> ~is_valid_object(arr[i])
    // assert forall i: 0 <= i -> i < cap -> is_allocated_space(arr + i)
    // assert 0 <= my_size
    // assert my_size <= cap

    while (!empty()) {

        pop_back();
    }

    if (cap != 0) {

        al.deallocate(arr, cap);
    }
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::back() {

    // assert 0 < my_size

    return arr[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::back() const {

    // assert 0 < my_size

    return arr[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::capacity() const {

    return cap;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::empty() const {

    return my_size == 0;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::full() const {

    return my_size == cap;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::pop_back() {

    // assert 0 < my_size

    al.destroy(arr + (my_size - 1));
    --my_size;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(const Type & Val) {

    // assert my_size < cap

    al.construct(arr + my_size, Val);
    ++my_size;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(Type && Val) {

    // assert my_size < cap

    al.construct(arr + my_size, std::forward<Type>(Val));
    ++my_size;
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::size() const {

    return my_size;
}

#endif // DEMO_VECTOR_H

