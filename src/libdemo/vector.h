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
            template<typename... Types> void emplace_back(Types&&... Args);
            bool empty() const;
            bool full() const;
            void pop_back();
            void push_back(const Type & Val);
            void push_back(Type && Val);
            size_type size() const;

        private:

            size_type my_size;
            size_type my_capacity;
            pointer my_array;
            Allocator my_allocator;

        // CLASS INVARIANT
        //
        // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
        // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
        // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
        // assert 0 <= my_size
        // assert my_size <= my_capacity
    };

    template<typename Type, typename Allocator = std::allocator<Type>>
    class vector {

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
            vector & operator=(const vector & Right);
            vector & operator=(vector && Right);

            vector();
            ~vector();

            reference back();
            const_reference back() const;
            size_type capacity() const;
            template<typename... Types> void emplace_back(Types&&... Args);
            bool empty() const;
            bool full() const;
            void pop_back();
            void push_back(const Type & Val);
            void push_back(Type && Val);
            size_type size() const;

        private:

            size_type my_size;
            size_type my_capacity;
            pointer my_array;
            Allocator my_allocator;

            void adjust_capacity(size_type NewSize);
            void set_capacity(size_type NewCapacity);

        // CLASS INVARIANT
        //
        // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
        // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
        // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
        // assert 0 <= my_size
        // assert my_size <= my_capacity
    };
}

//
// Demo::vector_fixed
//

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) {

    // assert 0 <= Pos
    // assert Pos < my_size

    return my_array[Pos];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::operator[](Demo::vector_fixed<Type, Allocator>::size_type Pos) const {

    // assert 0 <= Pos
    // assert Pos < my_size

    return my_array[Pos];
}

template<typename Type, typename Allocator>
Demo::vector_fixed<Type, Allocator>::vector_fixed(Demo::vector_fixed<Type, Allocator>::size_type Count) {

    // assert 0 <= Count

    if (Count != 0) {

        // ->
        // assert 0 < Count

        my_array = my_allocator.allocate(Count, nullptr);
        if (my_array == nullptr) {

            throw std::bad_alloc();
        }
    }
    else {

        // ->
        // assert 0 = Count

        my_array = nullptr;
    }

    my_size = static_cast<Demo::vector_fixed<Type, Allocator>::size_type>(0);
    my_capacity = Count;

    // ->
    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
    // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
    // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
    // assert 0 <= my_size
    // assert my_size <= my_capacity
}

template<typename Type, typename Allocator>
Demo::vector_fixed<Type, Allocator>::~vector_fixed() {

    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
    // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
    // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
    // assert 0 <= my_size
    // assert my_size <= my_capacity

    while (!empty()) {

        pop_back();
    }

    if (my_capacity != 0) {

        my_allocator.deallocate(my_array, my_capacity);
    }
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::reference Demo::vector_fixed<Type, Allocator>::back() {

    // assert 0 < my_size

    return my_array[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::const_reference Demo::vector_fixed<Type, Allocator>::back() const {

    // assert 0 < my_size

    return my_array[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::capacity() const {

    return my_capacity;
}

template<typename Type, typename Allocator>
template<typename... Types>
void Demo::vector_fixed<Type, Allocator>::emplace_back(Types&&... Args) {

    // assert my_size < my_capacity

    my_allocator.construct(my_array + my_size, std::forward<Types>(Args)...);
    ++my_size;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::empty() const {

    return my_size == 0;
}

template<typename Type, typename Allocator>
bool Demo::vector_fixed<Type, Allocator>::full() const {

    return my_size == my_capacity;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::pop_back() {

    // assert 0 < my_size

    my_allocator.destroy(my_array + (my_size - 1));
    --my_size;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(const Type & Val) {

    // assert my_size < my_capacity

    my_allocator.construct(my_array + my_size, Val);
    ++my_size;
}

template<typename Type, typename Allocator>
void Demo::vector_fixed<Type, Allocator>::push_back(Type && Val) {

    // assert my_size < my_capacity

    my_allocator.construct(my_array + my_size, std::forward<Type>(Val));
    ++my_size;
}

template<typename Type, typename Allocator>
typename Demo::vector_fixed<Type, Allocator>::size_type Demo::vector_fixed<Type, Allocator>::size() const {

    return my_size;
}

//
// Demo::vector
//

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::adjust_capacity(Demo::vector<Type, Allocator>::size_type NewSize) {

    // We want the ratio of NewSize / my_capacity in the interval
    // [0.25,1.00].
    if ((my_capacity < NewSize) || (NewSize < my_capacity / 4)) {

        // Ratio of NewSize / my_capacity is outside of desired
        // interval. Adjust to center of desired interval.
        set_capacity(NewSize * 2);
    }
    else if (NewSize == 0 && my_capacity != 0) {

        set_capacity(0);
    }
}

#endif // DEMO_VECTOR_H

