#include "demo/log.h"
#include "demo/vector.h"
#include "demo/verbose.h"

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
        // Vector object created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy(const verbose_copy & Right)") == 0);
        global_log.pop();
        // Temporary object destroyed
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());

        vec.push_back(verbose_copy(4));
        global_log.clear();
        vec.pop_back();
        // Vector object destroyed
        CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());
    }

    // Vector object destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    CPPUNIT_ASSERT(global_log.empty());
}

