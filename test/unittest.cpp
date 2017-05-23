#include <memory>

#include "cppunit/CompilerOutputter.h"
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"

int main() {

    using std::make_unique;
    using std::unique_ptr;

    // Get the top level suite from the registry
    unique_ptr<CppUnit::Test> suite{CppUnit::TestFactoryRegistry::getRegistry().makeTest()};

    // Adds the test to the list of test to run
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite.get());

    // Change the default outputter to a compiler error format outputter
    unique_ptr<CppUnit::CompilerOutputter> outputter = make_unique<CppUnit::CompilerOutputter>(&runner.result(), std::cerr);
    runner.setOutputter(outputter.get());

    // Run the tests.
    bool wasSucessful = runner.run();

    // Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}

