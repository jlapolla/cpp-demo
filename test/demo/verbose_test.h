#ifndef DEMO_VERBOSE_TEST_H
#define DEMO_VERBOSE_TEST_H

#include "cppunit/extensions/HelperMacros.h"

namespace DemoTest {

    class verbose_copy_container_test : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(verbose_copy_container_test);
        CPPUNIT_TEST(testInitializesMember);
        CPPUNIT_TEST_SUITE_END();

        public:

            void setUp();
            void tearDown();
            void testInitializesMember();
    };
}

#endif // DEMO_VERBOSE_TEST_H

