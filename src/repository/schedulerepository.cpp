#include "schedulerepository.h"

#include <sqlite_modern_cpp.h>

#include "resources/query.h"

namespace repository {

ScheduleRepository::ScheduleRepository() :
    _db{new sqlite::database(query::databseName())} { }

ScheduleRepository::~ScheduleRepository() {
    delete _db;
}

std::vector<model::ScheduleModel> ScheduleRepository::getSchedules() {
    sqlite::database db{query::databseName()};
    std::string const sql = query::find_schedule();
    datetime::DateTime dtNow = datetime::DateTime::now();

    std::vector<model::ScheduleModel> schedules;

    db << sql >>
        [&](int idSchedule, std::string const& title, std::string const& url, std::string const& sDtEvent, int nrWeekday, std::string const& sTmStart) -> void {
        model::ScheduleModel schedule;
        schedule.setIdSchedule(idSchedule);
        schedule.setTitle(title);
        schedule.setUrl(url);

        auto dtEvent = datetime::DateTime::fromString(sDtEvent);
        if (!dtEvent.isValid() && nrWeekday > 0) {
            int diff = nrWeekday - dtNow.weekDay();
            dtEvent = dtNow;
            dtEvent.addDays(diff);
            dtEvent.setTime(datetime::Time::fromString(sTmStart));
        }

        schedule.setDtEvent(dtEvent);
        schedules.push_back(schedule);
    };

    return schedules;
}

}
