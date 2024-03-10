#include <csignal>
#include <functional>
#include <spdlog/spdlog.h>

#include "eventloop/eventloop.h"
#include "migrate/migrate.h"
#include "service/scheduleservice.h"
#include "signal/signalhandler.h"

int main() {
    spdlog::info("{} starting...", __PRETTY_FUNCTION__);

    migrate::Migrate().update();

    service::ScheduleService schedule;

    spdlog::info("{} started", __PRETTY_FUNCTION__);
    eventloop::EventLoop event;
    event.addEvent(&schedule);
    event.setTimeout(50);

    signals::SignalHandler::instance().addHandler(SIGINT, [&event](int) -> bool {
        spdlog::info("{} ending", __PRETTY_FUNCTION__);
        event.shutdown();
        return true;
    });

    event.exec();

    return EXIT_SUCCESS;
}
