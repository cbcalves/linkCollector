#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <mutex>

#include "eventitem.h"

namespace eventloop {

class EventLoop {
public:
    void exec();

    void shutdown();

    void addEvent(EventItem&& event);

    long timeout() const;
    void setTimeout(long timeout);

private:
    std::mutex _mutex;
    std::vector<EventItem> _events{};
    long _timeout{5};
    bool _shutdown{false};
};

}

#endif // EVENTLOOP_H
