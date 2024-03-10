#include "scheduleservice.h"

#include "service/linkservice.h"

namespace {

constexpr int second = 1000;
constexpr int minute = 60 * second;

}

namespace service {

ScheduleService::ScheduleService() { }

int ScheduleService::exec() {
    std::vector<model::ScheduleModel> schedules = _repository.getSchedules();
    if (schedules.empty()) {
        return minute;
    }

    datetime::DateTime dtNow = datetime::DateTime::now();

    LinkService link;

    for (auto it = schedules.begin(); it != schedules.end(); ++it) {
        if (it->dtEvent() > dtNow) {
            continue;
        }

        link.process(*it);
    }

    return minute;
}

}
