#ifndef DEMO_LOG_TEST_H
#define DEMO_LOG_TEST_H

#include "cppunit/extensions/HelperMacros.h"

#include "demo/log.h"

namespace DemoTest {

    class log_test : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(log_test);
        CPPUNIT_TEST(testShouldFail);
        CPPUNIT_TEST(testShouldSucceed);
        CPPUNIT_TEST_SUITE_END();

        public:

            void setUp();
            void tearDown();
            void testShouldFail();
            void testShouldSucceed();
    };
}

#endif // DEMO_LOG_TEST_H

