#include "eventloop.h"

#include <chrono>
#include <condition_variable>

namespace eventloop {

void EventLoop::addEvent(EventItem&& event) {
    _events.push_back(std::move(event));
}

void EventLoop::shutdown() {
    _shutdown = true;
}

void EventLoop::exec() {
    std::condition_variable conditionVariable;
    std::unique_lock<std::mutex> lock(_mutex);

    while (!_shutdown) {
        auto const start = std::chrono::system_clock::now();
        auto const sleeptime = start + std::chrono::milliseconds(_timeout);

        for (auto const& event : _events) {
            event.exec();
        }

        conditionVariable.wait_until(lock, sleeptime);
    }
}

long EventLoop::timeout() const {
    return _timeout;
}

void EventLoop::setTimeout(long timeout) {
    if (timeout < 0) {
        return;
    }
    _timeout = timeout;
}

}
