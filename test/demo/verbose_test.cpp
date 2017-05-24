#include "demo/log.h"
#include "demo/verbose.h"

#include "verbose_test.h"

using namespace DemoTest;
using namespace Demo;

CPPUNIT_TEST_SUITE_REGISTRATION(verbose_copy_container_test);

void verbose_copy_container_test::setUp() {

    global_log.clear();
}

void verbose_copy_container_test::tearDown() {}

void verbose_copy_container_test::testInitializesMember() {

    {

        verbose_container<verbose_copy> x;
        // Object and member created
        CPPUNIT_ASSERT(global_log.front().compare("verbose_copy()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.front().compare("verbose_container()") == 0);
        global_log.pop();
        CPPUNIT_ASSERT(global_log.empty());
    }

    // Object and member destroyed
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_container()") == 0);
    global_log.pop();
    CPPUNIT_ASSERT(global_log.front().compare("~verbose_copy()") == 0);
    global_log.pop();
    CPPUNIT_ASSERT(global_log.empty());
}

