#ifndef SIGNALHANDLER_H
#define SIGNALHANDLER_H

#include <functional>
#include <map>

namespace signals {

class SignalHandler {
public:
    static SignalHandler& instance();

    void addHandler(int sig, std::function<bool(int)> newHandler);
    void removeHandler(int sig);

    std::function<bool(int)> handler(int sig);

private:
    std::map<int, std::function<bool(int)>> _handlers{};

    SignalHandler() = default;
    SignalHandler(SignalHandler const&) = delete;
    SignalHandler& operator=(SignalHandler const&) const = delete;
};

}

#endif // SIGNALHANDLER_H
