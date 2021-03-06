#ifndef DEMO_VECTOR_TEST_H
#define DEMO_VECTOR_TEST_H

#include "cppunit/extensions/HelperMacros.h"

namespace DemoTest {

    class vector_fixed_test : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(vector_fixed_test);
        CPPUNIT_TEST(testManagesCopyableType);
        CPPUNIT_TEST(testManagesUniquePtrType);
        CPPUNIT_TEST(testWorksWithZeroCapacity);
        CPPUNIT_TEST(testSubscriptOperator);
        CPPUNIT_TEST(testFullAndEmpty);
        CPPUNIT_TEST(testSizeAndCapacity);
        CPPUNIT_TEST(testBack);
        CPPUNIT_TEST_SUITE_END();

        public:

            void setUp();
            void tearDown();
            void testManagesCopyableType();
            void testManagesUniquePtrType();
            void testWorksWithZeroCapacity();
            void testSubscriptOperator();
            void testFullAndEmpty();
            void testSizeAndCapacity();
            void testBack();
    };

    class vector_test : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(vector_test);
        CPPUNIT_TEST(testManagesCopyableType);
        CPPUNIT_TEST_SUITE_END();

        public:

            void setUp();
            void tearDown();
            void testManagesCopyableType();
    };
}

#endif // DEMO_VECTOR_TEST_H

