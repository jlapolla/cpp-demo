#ifndef DEMO_LOG_H
#define DEMO_LOG_H

#include <memory>
#include <queue>
#include <string>

#include "logger.h"

namespace Demo {

    using std::queue;
    using std::string;
    using std::unique_ptr;

    class log : public logger {

        public:

            typedef queue<string>::size_type size_type;
            typedef queue<string>::value_type value_type;
            typedef const value_type & const_reference;

            log & operator=(const log & Right) = delete;
            log & operator=(log && Right);

            log(const log & Right) = delete;
            log(log && Right);
            log();

            const_reference back() const;
            bool empty() const;
            const_reference front() const;
            void pop();
            void push(const_reference message);
            void push_back(const_reference message) override;
            size_type size() const;

        private:

            unique_ptr<queue<string>> messages;
    };
}

#endif // DEMO_LOG_H

