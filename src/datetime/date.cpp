#include "date.h"

namespace datetime {

Date::Date() { }

Date::Date(int year, int unsigned month, int unsigned day) :
    _ymd(std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}) { }

Date::Date(std::chrono::year_month_day ymd) :
    _ymd(ymd) { }

Date Date::now() {
    // TODO: select timezone
    std::chrono::time_point const tpNow{std::chrono::system_clock::now()};
    std::chrono::year_month_day const ymd{std::chrono::floor<std::chrono::days>(tpNow)};

    return Date(ymd);
}

bool Date::isValid() {
    return _ymd.ok();
}

int Date::year() const {
    return static_cast<int>(_ymd.year());
}

void Date::setYear(int year) {
    _ymd = std::chrono::year_month_day{std::chrono::year{year}, _ymd.month(), _ymd.day()};
}

int unsigned Date::month() const {
    return static_cast<int unsigned>(_ymd.month());
}

void Date::setMonth(int unsigned month) {
    _ymd = std::chrono::year_month_day{_ymd.year(), std::chrono::month{month}, _ymd.day()};
}

int unsigned Date::day() const {
    return static_cast<int unsigned>(_ymd.day());
}

void Date::setDay(int unsigned day) {
    _ymd = std::chrono::year_month_day{_ymd.year(), _ymd.month(), std::chrono::day{day}};
}

int Date::weekDay() const {
    std::chrono::weekday wday{std::chrono::sys_days(_ymd)};
    return wday.c_encoding();
}

bool Date::operator<(Date other) {
    return date() < other.date();
}

bool Date::operator>(Date other) {
    return date() > other.date();
}

bool Date::operator==(Date other) {
    return date() == other.date();
}

std::chrono::year_month_day Date::date() const {
    return _ymd;
}

void Date::setDate(std::chrono::year_month_day ymd) {
    _ymd = ymd;
}

}
