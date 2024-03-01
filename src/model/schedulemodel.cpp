#include "schedulemodel.h"

namespace model {

std::string ScheduleModel::title() const {
    return _title;
}

void ScheduleModel::setTitle(const std::string& title) {
    _title = title;
}

std::string ScheduleModel::url() const {
    return _url;
}

void ScheduleModel::setUrl(const std::string& url) {
    _url = url;
}

datetime::DateTime ScheduleModel::dtEvent() const {
    return _dtEvent;
}

void ScheduleModel::setDtEvent(datetime::DateTime const dtEvent) {
    _dtEvent = dtEvent;
}

int ScheduleModel::idSchedule() const {
    return _idSchedule;
}

void ScheduleModel::setIdSchedule(int idSchedule) {
    _idSchedule = idSchedule;
}

}
