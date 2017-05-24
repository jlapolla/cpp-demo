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
        // assert (my_capacity = 0) = (my_array = nullptr)
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
typename Demo::vector<Type, Allocator>::reference Demo::vector<Type, Allocator>::operator[](Demo::vector<Type, Allocator>::size_type Pos) {

    // assert 0 <= Pos
    // assert Pos < my_size

    return my_array[Pos];
}

template<typename Type, typename Allocator>
typename Demo::vector<Type, Allocator>::const_reference Demo::vector<Type, Allocator>::operator[](Demo::vector<Type, Allocator>::size_type Pos) const {

    // assert 0 <= Pos
    // assert Pos < my_size

    return my_array[Pos];
}

template<typename Type, typename Allocator>
Demo::vector<Type, Allocator>::vector() :
    my_size(static_cast<Demo::vector<Type, Allocator>::size_type>(0)),
    my_capacity(static_cast<Demo::vector<Type, Allocator>::size_type>(0)),
    my_array(nullptr)
{

    // ->
    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
    // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
    // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
    // assert 0 <= my_size
    // assert my_size <= my_capacity
    // assert (my_capacity = 0) = (my_array = nullptr)
}

template<typename Type, typename Allocator>
Demo::vector<Type, Allocator>::~vector() {

    // assert forall i: 0 <= i -> i < my_size -> is_valid_object(my_array[i])
    // assert forall i: my_size <= i -> i < my_capacity -> ~is_valid_object(my_array[i])
    // assert forall i: 0 <= i -> i < my_capacity -> is_allocated_space(my_array + i)
    // assert 0 <= my_size
    // assert my_size <= my_capacity
    // assert (my_capacity = 0) = (my_array = nullptr)

    while (!empty()) {

        pop_back();
    }

    if (my_capacity != 0) {

        my_allocator.deallocate(my_array, my_capacity);
    }
}

template<typename Type, typename Allocator>
typename Demo::vector<Type, Allocator>::reference Demo::vector<Type, Allocator>::back() {

    // assert 0 < my_size

    return my_array[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector<Type, Allocator>::const_reference Demo::vector<Type, Allocator>::back() const {

    // assert 0 < my_size

    return my_array[my_size - 1];
}

template<typename Type, typename Allocator>
typename Demo::vector<Type, Allocator>::size_type Demo::vector<Type, Allocator>::capacity() const {

    return my_capacity;
}

template<typename Type, typename Allocator>
template<typename... Types>
void Demo::vector<Type, Allocator>::emplace_back(Types&&... Args) {

    adjust_capacity(my_size + 1);
    my_allocator.construct(my_array + my_size, std::forward<Types>(Args)...);
    ++my_size;
}

template<typename Type, typename Allocator>
bool Demo::vector<Type, Allocator>::empty() const {

    return my_size == 0;
}

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::pop_back() {

    // assert 0 < my_size

    my_allocator.destroy(my_array + (my_size - 1));
    --my_size;
    adjust_capacity(my_size);
}

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::push_back(const Type & Val) {

    adjust_capacity(my_size + 1);
    my_allocator.construct(my_array + my_size, Val);
    ++my_size;
}

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::push_back(Type && Val) {

    adjust_capacity(my_size + 1);
    my_allocator.construct(my_array + my_size, std::forward<Type>(Val));
    ++my_size;
}

template<typename Type, typename Allocator>
typename Demo::vector<Type, Allocator>::size_type Demo::vector<Type, Allocator>::size() const {

    return my_size;
}

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::adjust_capacity(Demo::vector<Type, Allocator>::size_type NewSize) {

    // assert my_size <= NewSize

    // For non-zero NewSize, we want the ratio of NewSize / my_capacity
    // in the interval [0.25,1.00]. If NewSize is zero, we want
    // my_capacity to be zero.

    // Note that the lower bound of the interval, 0.25, is approximate.
    // For example, if my_capacity = 7 and NewSize = 1, then
    // 'my_capacity / 4' is 1 after truncation, and the capacity is not
    // reset. This yields an actual ratio of 0.14, which is less than
    // the desired lower bound of 0.25.

    if ((my_capacity < NewSize) || (NewSize < my_capacity / 4)) {

        // Ratio of NewSize / my_capacity is outside of desired
        // interval. Adjust ratio to 0.5.

        set_capacity(NewSize * 2);
    }
    else if (NewSize == 0 && my_capacity != 0) {

        // This branch is necessary because of truncation when computing
        // 'my_capacity / 4'. E.g. if NewSize = 0 and my_capacity = 1,
        // we must set my_capacity to zero, but the previous branch will
        // not be executed since 'my_capacity / 4' evaluates to zero
        // after truncation.

        set_capacity(0);
    }
}

template<typename Type, typename Allocator>
void Demo::vector<Type, Allocator>::set_capacity(Demo::vector<Type, Allocator>::size_type NewCapacity) {

    // assert my_size <= NewCapacity

    // Allocate NewArray[NewCapacity]

    pointer NewArray;
    if (NewCapacity != 0) {

        // ->
        // assert 0 < NewCapacity

        NewArray = my_allocator.allocate(NewCapacity, my_array);
        if (NewArray == nullptr) {

            throw std::bad_alloc();
        }
    }
    else {

        // ->
        // assert 0 = NewCapacity

        NewArray = nullptr;
    }

    // Move my_array[0:my_size] elements to NewArray

    size_type i = static_cast<size_type>(0);
    while (i < my_size) {

        my_allocator.contruct(NewArray + i, std::move<Type>(my_array[i]));
        my_allocator.destroy(my_array + i);
        ++i;
    }

    // Deallocate my_array

    if (my_capacity != 0) {

        my_allocator.deallocate(my_array, my_capacity);
    }

    my_array = NewArray;
    my_capacity = NewCapacity;
}

#endif // DEMO_VECTOR_H

