#ifndef DATETIME_H
#define DATETIME_H

#include "date.h"
#include "time.h"

namespace datetime {

class DateTime : public Date, public Time {
public:
    DateTime();
    explicit DateTime(int year, int unsigned month, int unsigned day, int unsigned hours = 0, int unsigned minutes = 0, int unsigned seconds = 0);
    explicit DateTime(std::chrono::year_month_day ymd, std::chrono::seconds hms);

    static DateTime now();

    std::string toString() const;
    static DateTime fromString(std::string const& str);

    Date date();
    Time time();

private:
    DateTime(Date date, Time time);
};

}

#endif // DATETIME_H
