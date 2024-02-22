#include "time.h"
#include <regex>

namespace {

int constexpr hours_a_day_to_seconds = 86400;
int constexpr hours_a_day = 24;
int constexpr seconds_an_hour = 3600;
int constexpr minutes_an_hour = 60;
int constexpr seconds_a_minute = 60;

}

namespace datetime {

Time::Time() { }

Time::Time(int unsigned hours, int unsigned minutes, int unsigned seconds) :
    _hms{std::chrono::seconds{(seconds % seconds_a_minute) + ((minutes % minutes_an_hour) * seconds_a_minute) + ((hours % hours_a_day) * seconds_an_hour)}} { }

Time::Time(std::chrono::seconds hms) :
    _hms{hms} { }

Time Time::now() {
    std::chrono::time_point tpNow{std::chrono::system_clock::now()};

    std::chrono::time_zone const* timeZone = std::chrono::current_zone();
    auto localTime = timeZone->to_local(tpNow);

    std::chrono::seconds hms{std::chrono::floor<std::chrono::seconds>(localTime.time_since_epoch()) % hours_a_day_to_seconds};
    return Time(hms);
}

int Time::hours() const {
    return _hms.count() / seconds_an_hour;
}

void Time::setHours(int unsigned hours) {
    hours = hours % hours_a_day;
    _hms = std::chrono::seconds{hours * seconds_an_hour} + (_hms % seconds_an_hour);
}

int Time::minutes() const {
    return (_hms.count() / minutes_an_hour) - (hours() * minutes_an_hour);
}

void Time::setMinutes(int unsigned minutes) {
    minutes = minutes % minutes_an_hour;
    _hms = std::chrono::seconds{minutes * seconds_a_minute} + (_hms % minutes_an_hour) + std::chrono::seconds{hours() * seconds_an_hour};
}

int Time::seconds() const {
    return _hms.count() % seconds_a_minute;
}

void Time::setSeconds(int unsigned seconds) {
    seconds = seconds % seconds_a_minute;
    _hms = (_hms - _hms % seconds_a_minute) + std::chrono::seconds{seconds};
}

std::string Time::toString() const {
    return std::format("{:0>2}:{:0>2}:{:0>2}", hours(), minutes(), seconds());
}

Time Time::fromString(const std::string& str) {
    static std::regex regex(R"-(^(\d{1,2}).(\d{1,2}).(\d{1,2})$)-");
    std::smatch smatch;
    if (!std::regex_match(str, smatch, regex)) {
        return {};
    }

    int unsigned const hh = std::stoi(smatch[1].str()) % 24;
    int unsigned const mm = std::stoi(smatch[2].str()) % 60;
    int unsigned const ss = std::stoi(smatch[3].str()) % 60;

    return Time(hh, mm, ss);
}

bool Time::operator<(Time other) {
    return time() < other.time();
}

bool Time::operator>(Time other) {
    return time() > other.time();
}

bool Time::operator==(Time other) {
    return time() == other.time();
}

std::chrono::seconds Time::time() const {
    return _hms;
}

void Time::setTime(std::chrono::seconds hms) {
    _hms = hms % hours_a_day_to_seconds;
}

}
