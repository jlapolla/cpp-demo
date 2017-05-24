#ifndef DEMO_VERBOSE_H
#define DEMO_VERBOSE_H

namespace Demo {

    class verbose_copy {

        public:

            typedef int value_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;

            verbose_copy & operator=(const verbose_copy & Right);

            verbose_copy();
            explicit verbose_copy(value_type Val);
            verbose_copy(const verbose_copy & Right);
            ~verbose_copy();

            reference value();
            const_reference value() const;

        private:

            value_type val;
    };

    template<typename Type>
    class verbose_container {

        public:

            verbose_container();
            ~verbose_container();

            Type & value();
            const Type & value() const;

        private:

            Type my_value;
    };
}

template<typename Type>
Demo::verbose_container<Type>::verbose_container() {

    global_logger->push_back("verbose_container()");
}

template<typename Type>
Demo::verbose_container<Type>::~verbose_container() {

    global_logger->push_back("~verbose_container()");
}

template<typename Type>
Type & Demo::verbose_container<Type>::value() {

    return my_value;
}

template<typename Type>
const Type & Demo::verbose_container<Type>::value() const {

    return my_value;
}

#endif // DEMO_VERBOSE_H

