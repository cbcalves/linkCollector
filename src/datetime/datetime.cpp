#include "datetime.h"

namespace datetime {

DateTime::DateTime() { }

DateTime::DateTime(int year, int unsigned month, int unsigned day, int unsigned hours, int unsigned minutes, int unsigned seconds) :
    Date{year, month, day},
    Time{hours, minutes, seconds} { }

DateTime::DateTime(std::chrono::year_month_day ymd, std::chrono::seconds hms) :
    Date{ymd},
    Time{hms} { }

DateTime DateTime::now() {
    return DateTime(Date::now(), Time::now());
}

Date DateTime::date() {
    return Date(Date::date());
}

Time DateTime::time() {
    return Time(Time::time());
}

DateTime::DateTime(Date date, Time time) :
    Date{date},
    Time{time} { }

}
