#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace datetime {

class Time {
public:
    Time();
    explicit Time(int unsigned hours, int unsigned minutes, int unsigned seconds);
    explicit Time(std::chrono::seconds hms);

    static Time now();

    int hours() const;
    void setHours(unsigned int hours);

    int minutes() const;
    void setMinutes(unsigned int minutes);

    int seconds() const;
    void setSeconds(unsigned int seconds);

    std::string toString() const;
    static Time fromString(std::string const& str);

    bool operator<(Time other);
    bool operator>(Time other);
    bool operator==(Time other);

protected:
    std::chrono::seconds time() const;
    void setTime(std::chrono::seconds hms);

private:
    std::chrono::seconds _hms{};
};

}

#endif // TIME_H
