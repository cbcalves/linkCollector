#include "date.h"
#include <regex>

namespace datetime {

Date::Date() { }

Date::Date(int year, int unsigned month, int unsigned day) :
    _ymd(std::chrono::year{year}, std::chrono::month{month}, std::chrono::day{day}) { }

Date::Date(std::chrono::year_month_day ymd) :
    _ymd(ymd) { }

Date Date::now() {
    std::chrono::time_point const tpNow{std::chrono::system_clock::now()};

    std::chrono::time_zone const* timeZone = std::chrono::current_zone();
    auto localTime = timeZone->to_local(tpNow);

    std::chrono::year_month_day const ymd{std::chrono::floor<std::chrono::days>(localTime)};

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

void Date::addDays(int days) {
    if (!isValid()) {
        setDay(day() + days);
        return;
    }

    while (days > 0) {
        setDay(day() + 1);
        if (!isValid()) {
            addMonths(1);
            setDay(1);
        }
        --days;
    }

    while (days < 0) {
        setDay(day() - 1);
        if (!isValid()) {
            addMonths(-1);
            setDay(31);
            while (!isValid()) {
                setDay(day() - 1);
            }
        }
        ++days;
    }
}

void Date::addMonths(int months) {
    bool const wasValid = isValid();
    _ymd = _ymd + std::chrono::months(months);
    if (wasValid && !isValid()) {
        while (!isValid()) {
            addDays(-1);
        }
    }
}

void Date::addYears(int years) {
    bool const wasValid = isValid();
    _ymd = _ymd + std::chrono::years(years);
    if (wasValid && !isValid()) {
        while (!isValid()) {
            addDays(-1);
        }
    }
}

int Date::weekDay() const {
    std::chrono::weekday wday{std::chrono::sys_days(_ymd)};
    return wday.c_encoding() + 1;
}

std::string Date::toString() const {
    return std::format("{}-{:0>2}-{:0>2}", year(), month(), day());
}

Date Date::fromString(const std::string& str) {
    static std::regex regex(R"-(^(\d{4}).(\d{1,2}).(\d{1,2})$)-");
    std::smatch smatch;
    if (!std::regex_match(str, smatch, regex)) {
        return {};
    }

    int const y = std::stoi(smatch[1].str());
    int unsigned const m = std::stoi(smatch[2].str());
    int unsigned const d = std::stoi(smatch[3].str());

    return Date(y, m, d);
}

bool Date::operator<(const Date other) const {
    return date() < other.date();
}

bool Date::operator>(const Date other) const {
    return date() > other.date();
}

bool Date::operator==(const Date other) const {
    return date() == other.date();
}

void Date::setDate(Date date) {
    _ymd = date.date();
}

std::chrono::year_month_day Date::date() const {
    return _ymd;
}

void Date::setDate(std::chrono::year_month_day ymd) {
    _ymd = ymd;
}

}
