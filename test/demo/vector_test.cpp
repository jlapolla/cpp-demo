#include <memory>
#include <utility>

#include "libdemo/log.h"
#include "libdemo/vector.h"
#include "libdemo/verbose.h"

#include "vector_test.h"

using namespace DemoTest;
using namespace Demo;

CPPUNIT_TEST_SUITE_REGISTRATION(vector_fixed_test);

void vector_fixed_test::setUp() {

    global_log.clear();
}

void vector_fixed_test::tearDown() {}

void vector_fixed_test::testManagesCopyableType() {

    {

        vector_fixed<verbose_copy> vec{5};
        // Space allocated, but not initialized
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(verbose_copy(3));
        // Temporary object created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(value_type Val)") == 0);
        global_log.pop();
        // Vector element created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(const verbose_copy & Right)") == 0);
        global_log.pop();
        // Temporary object destroyed
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        const verbose_copy x{4};
        // 'x' object created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(value_type Val)") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(x);
        // Vector element created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(const verbose_copy & Right)") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        verbose_copy y{4};
        // 'y' object created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(value_type Val)") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(y);
        // Vector element created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(const verbose_copy & Right)") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.pop_back();
        // Vector element destroyed
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());
    }

    // 'y' object destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    // 'x' object destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    // 'vec' object destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    // 'vec' object destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    CPPUNIT_ASSERT(global_log.empty());
}

void vector_fixed_test::testManagesUniquePtrType() {

    using std::make_unique;
    using std::move;
    using std::unique_ptr;

    unique_ptr<verbose_copy> a{make_unique<verbose_copy>(0)};
    verbose_copy * py;

    {

        unique_ptr<verbose_copy> x{make_unique<verbose_copy>(1)};
        unique_ptr<verbose_copy> y{make_unique<verbose_copy>(2)};

        py = y.get();

        global_log.clear();

        vector_fixed<unique_ptr<verbose_copy>> vec{5};
        // Space allocated, but not initialized
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(move(x));
        vec.push_back(move(y));
        // Moved unique_ptr
        CPPUNIT_ASSERT(global_log.empty());

        a = move(vec[1]);
        // Destroyed previous contents of 'a'
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.pop_back();
        // Destroyed empty unique_ptr
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(make_unique<verbose_copy>(2));
        // New object created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(value_type Val)") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.pop_back();
        // Destroyed unique_ptr and object
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());
    }

    // Destroyed unique_ptr and object
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    CPPUNIT_ASSERT(global_log.empty());

    CPPUNIT_ASSERT(a->value() == 2);
    CPPUNIT_ASSERT(a.get() == py);
}

void vector_fixed_test::testWorksWithZeroCapacity() {

    vector_fixed<int> vec{0};

    CPPUNIT_ASSERT(vec.size() == 0);
    CPPUNIT_ASSERT(vec.capacity() == 0);
}

void vector_fixed_test::testSubscriptOperator() {

    vector_fixed<int> vec{5};
    vec.push_back(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    CPPUNIT_ASSERT(vec[0] == 0);
    CPPUNIT_ASSERT(vec[2] == 2);
    CPPUNIT_ASSERT(vec[4] == 4);

    vec[4] = 100;

    CPPUNIT_ASSERT(vec[4] == 100);
}

void vector_fixed_test::testFullAndEmpty() {

    vector_fixed<int> vec{3};
    CPPUNIT_ASSERT(vec.empty());
    CPPUNIT_ASSERT(!vec.full());

    vec.push_back(0);
    CPPUNIT_ASSERT(!vec.empty());
    CPPUNIT_ASSERT(!vec.full());

    vec.push_back(1);
    CPPUNIT_ASSERT(!vec.empty());
    CPPUNIT_ASSERT(!vec.full());

    vec.push_back(2);
    CPPUNIT_ASSERT(!vec.empty());
    CPPUNIT_ASSERT(vec.full());

    vec.pop_back();
    CPPUNIT_ASSERT(!vec.empty());
    CPPUNIT_ASSERT(!vec.full());

    vec.pop_back();
    CPPUNIT_ASSERT(!vec.empty());
    CPPUNIT_ASSERT(!vec.full());

    vec.pop_back();
    CPPUNIT_ASSERT(vec.empty());
    CPPUNIT_ASSERT(!vec.full());
}

