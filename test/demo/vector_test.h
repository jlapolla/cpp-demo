#ifndef DEMO_VECTOR_TEST_H
#define DEMO_VECTOR_TEST_H

#include "cppunit/extensions/HelperMacros.h"

namespace DemoTest {

    class vector_fixed_test : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(vector_fixed_test);
        CPPUNIT_TEST(testManagesCopyableType);
        CPPUNIT_TEST(testManagesUniquePtrType);
        CPPUNIT_TEST_SUITE_END();

        public:

            void setUp();
            void tearDown();
            void testManagesCopyableType();
            void testManagesUniquePtrType();
    };
}

#endif // DEMO_VECTOR_TEST_H

