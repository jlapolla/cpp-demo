#include <iostream>

#include "logger.h"
#include "verbose.h"

Demo::verbose_copy & Demo::verbose_copy::operator=(const Demo::verbose_copy & Right) {

    global_logger->push_back("verbose_copy & operator=(const verbose_copy & Right)");
    std::cerr << "verbose_copy & operator=(const verbose_copy & Right)" << std::endl;
    val = Right.val;
    return *this;
}

Demo::verbose_copy::verbose_copy(Demo::verbose_copy::value_type Val) {

    global_logger->push_back("verbose_copy(value_type Val)" );
    std::cerr << "verbose_copy(value_type Val)" << std::endl;
    val = Val;
}

Demo::verbose_copy::verbose_copy(const Demo::verbose_copy & Right) {

    global_logger->push_back("verbose_copy(const verbose_copy & Right)" );
    std::cerr << "verbose_copy(const verbose_copy & Right)" << std::endl;
    val = Right.val;
}

Demo::verbose_copy::~verbose_copy() {

    global_logger->push_back("~verbose_copy()" );
    std::cerr << "~verbose_copy()" << std::endl;
}

Demo::verbose_copy::reference Demo::verbose_copy::value() {

    return val;
}

Demo::verbose_copy::const_reference Demo::verbose_copy::value() const {

    return val;
}

