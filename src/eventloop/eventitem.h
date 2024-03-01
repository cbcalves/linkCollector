#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <chrono>
#include <functional>

namespace eventloop {

class EventItem {
public:
    template<class Event>
    EventItem(Event* ptr) :
        _ptr{ptr},
        _exec{getMethod<Event>(&Event::exec)} { }

    inline int exec() const { return _exec(_ptr); }

    inline std::chrono::milliseconds next() const { return _next; };
    inline void setNext(std::chrono::milliseconds const next) { _next = next; }

private:
    std::function<int(void*)> _exec;
    void* _ptr{nullptr};
    std::chrono::milliseconds _next{};

    template<class Event, typename Func>
    std::function<int(void*)> getMethod(Func f) {
        return [f](void* p) -> int {
            return (reinterpret_cast<Event*>(p)->*f)();
        };
    }
};

}

#endif // EVENTITEM_H
