#include <memory>

#include "cppunit/CompilerOutputter.h"
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"

int main() {

    using std::make_unique;
    using std::unique_ptr;

    // Get the top level test suite from the registry
    unique_ptr<CppUnit::Test> suite{CppUnit::TestFactoryRegistry::getRegistry().makeTest()};

    // Add the test suite to the list of tests to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite.release());

    // Change the default outputter
    unique_ptr<CppUnit::CompilerOutputter> outputter = make_unique<CppUnit::CompilerOutputter>(&runner.result(), std::cerr);
    runner.setOutputter(outputter.release());

    // Run tests
    bool success = runner.run();

    // Return 1 on failure
    return success ? 0 : 1;
}

