#include "signalhandler.h"

#include <csignal>
#include <spdlog/spdlog.h>

namespace signals {

void signalHandler(int sig) {
    spdlog::info("{} [signal]{}", __FUNCTION__, sig);
    auto handler = signals::SignalHandler::instance().handler(sig);
    if (handler && handler(sig)) {
        return;
    }

    signal(sig, SIG_DFL);
}

SignalHandler& SignalHandler::instance() {
    static SignalHandler signalHandler;
    return signalHandler;
}

void SignalHandler::addHandler(int sig, std::function<bool(int)> newHandler) {
    spdlog::debug("{} [signal]{}", __PRETTY_FUNCTION__, sig);

    _handlers.emplace(sig, newHandler);
    signal(sig, signalHandler);
}

void SignalHandler::removeHandler(int sig) {
    spdlog::debug("{} [signal]{}", __PRETTY_FUNCTION__, sig);
    signal(sig, SIG_DFL);

    auto it = _handlers.find(sig);
    if (it != _handlers.end()) {
        _handlers.erase(it);
    }
}

std::function<bool(int)> SignalHandler::handler(int sig) {
    spdlog::debug("{} [signal]{}", __PRETTY_FUNCTION__, sig);

    if (_handlers.contains(sig)) {
        return _handlers.at(sig);
    }

    return nullptr;
}

}
