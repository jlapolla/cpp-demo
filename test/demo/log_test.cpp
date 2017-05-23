#include "log_test.h"

using namespace DemoTest;

CPPUNIT_TEST_SUITE_REGISTRATION(log_test);

void log_test::setUp() {}

void log_test::tearDown() {}

void log_test::testShouldFail() {

    CPPUNIT_ASSERT(false);
}

void log_test::testShouldSucceed() {

    CPPUNIT_ASSERT(true);
}

