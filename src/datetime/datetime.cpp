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

std::string DateTime::toString() const {
    return Date::toString() + ' ' + Time::toString();
}

DateTime DateTime::fromString(const std::string& str) {
    if (str.size() != 19) {
        return {};
    }
    std::string dt = str.substr(0, 10);
    std::string tm = str.substr(11);

    return DateTime(Date::fromString(dt), Time::fromString(tm));
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
