#ifndef DATE_H
#define DATE_H

#include <chrono>

namespace datetime {

class Date {
public:
    Date();
    explicit Date(int year, unsigned int month, unsigned int day);
    explicit Date(std::chrono::year_month_day ymd);

    static Date now();

    bool isValid();

    int year() const;
    void setYear(int year);

    int unsigned month() const;
    void setMonth(int unsigned month);

    int unsigned day() const;
    void setDay(int unsigned day);

    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);

    int weekDay() const;

    std::string toString() const;
    static Date fromString(std::string const& str);

    bool operator<(const Date other) const;
    bool operator>(const Date other) const;
    bool operator==(const Date other) const;

    void setDate(Date date);

protected:
    std::chrono::year_month_day date() const;
    void setDate(std::chrono::year_month_day ymd);

private:
    std::chrono::year_month_day _ymd{};
};

}

#endif // DATE_H
