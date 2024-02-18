#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <functional>

namespace eventloop {

class EventItem {
public:
    template<class Event>
    EventItem(Event* ptr) :
        _ptr{ptr},
        _exec{getMethod<Event>(&Event::exec)} { }

    inline void exec() const { _exec(_ptr); }

private:
    std::function<void(void*)> _exec;
    void* _ptr{nullptr};

    template<class Event, typename Func>
    std::function<void(void*)> getMethod(Func f) {
        return [f](void* p) -> void {
            (reinterpret_cast<Event*>(p)->*f)();
        };
    }
};

}

#endif // EVENTITEM_H
