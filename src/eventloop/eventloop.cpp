#include "eventloop.h"

#include <chrono>
#include <condition_variable>
#include <spdlog/spdlog.h>

namespace eventloop {

void EventLoop::addEvent(EventItem&& event) {
    _events.push_back(std::move(event));
}

void EventLoop::shutdown() {
    spdlog::info("{}", __PRETTY_FUNCTION__);
    _shutdown = true;
}

void EventLoop::exec() {
    std::condition_variable conditionVariable;
    std::unique_lock<std::mutex> lock(_mutex);

    while (!_shutdown) {
        auto const start = std::chrono::system_clock::now();
        auto const sleeptime = start + std::chrono::milliseconds(_timeout);

        auto const startMilliseconds = std::chrono::floor<std::chrono::milliseconds>(start).time_since_epoch();
        for (auto& event : _events) {
            if (!_shutdown && event.next() < startMilliseconds) {
                const int interval = event.exec();
                event.setNext(startMilliseconds + std::chrono::milliseconds{interval});
            }
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
