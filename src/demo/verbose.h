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

    class verbose_copy_container {

        public:

            verbose_copy_container();
            ~verbose_copy_container();

            verbose_copy & value();
            const verbose_copy & value() const;

        private:

            verbose_copy my_verbose;
    };
}

#endif // DEMO_VERBOSE_H

