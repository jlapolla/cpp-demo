#include "logger.h"
#include "verbose.h"

using namespace Demo;

verbose_copy & verbose_copy::operator=(const verbose_copy & Right) {

    global_logger->push_back("verbose_copy & operator=(const verbose_copy & Right)");
    val = Right.val;
    return *this;
}

verbose_copy::verbose_copy(verbose_copy::value_type Val) {

    global_logger->push_back("verbose_copy(value_type Val)" );
    val = Val;
}

verbose_copy::verbose_copy(const verbose_copy & Right) {

    global_logger->push_back("verbose_copy(const verbose_copy & Right)" );
    val = Right.val;
}

verbose_copy::~verbose_copy() {

    global_logger->push_back("~verbose_copy()" );
}

verbose_copy::reference verbose_copy::value() {

    return val;
}

verbose_copy::const_reference verbose_copy::value() const {

    return val;
}

