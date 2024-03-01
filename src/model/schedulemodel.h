#ifndef SCHEDULEMODEL_H
#define SCHEDULEMODEL_H

#include <string>

#include "datetime/datetime.h"

namespace model {

class ScheduleModel {
public:
    std::string title() const;
    void setTitle(const std::string& title);

    std::string url() const;
    void setUrl(const std::string& url);

    datetime::DateTime dtEvent() const;
    void setDtEvent(datetime::DateTime const dtEvent);

    int idSchedule() const;
    void setIdSchedule(int idSchedule);

    inline bool operator<(ScheduleModel const& other) const { return _dtEvent < other._dtEvent; }

private:
    std::string _title{};
    std::string _url{};
    datetime::DateTime _dtEvent{};
    int _idSchedule{};
};

}

#endif // SCHEDULEMODEL_H
