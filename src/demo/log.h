#ifndef DEMO_LOG_H
#define DEMO_LOG_H

#include <queue>
#include <string>

namespace Demo {

    using std::queue;
    using std::string;

    class log {

        public:

            typedef queue<string> container_type;
            typedef container_type::size_type size_type;
            typedef container_type::value_type value_type;
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
            size_type size() const;

        private:

            queue<string> messages;
    }
}

#endif // DEMO_LOG_H

