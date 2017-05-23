#ifndef DEMO_LOGGER_H
#define DEMO_LOGGER_H

#include <string>

namespace Demo {

    using std::string;

    class logger {

        public:

            virtual void push_back(const string & message) = 0;
    };

    extern logger * global_logger;
}

#endif // DEMO_LOGGER_H

