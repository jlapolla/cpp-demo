#include <memory>
#include <queue>
#include <string>
#include <utility>

#include "log.h"

using namespace Demo;
using std::make_unique;
using std::move;

log & log::operator=(log && Right) {

    messages = move(Right.messages);
    return *this;
}

log::log(log && Right) {

    messages = move(Right.messages);
}

log::log() {

    messages = make_unique<queue<string>>();
}

log::const_reference log::back() const {

    return messages->back();
}

bool log::empty() const {

    return messages->empty();
}

log::const_reference log::front() const {

    return messages->front();
}

void log::pop() {

    messages->pop();
}

void log::push(log::const_reference message) {

    messages->push(message);
}

void log::push_back(log::const_reference message) {

    messages->push(message);
}

log::size_type log::size() const {

    return messages->size();
}

