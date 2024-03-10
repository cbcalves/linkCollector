#ifndef SCHEDULEREPOSITORY_H
#define SCHEDULEREPOSITORY_H

#include "model/schedulemodel.h"

namespace sqlite {
class database;
}

namespace repository {

class ScheduleRepository {
public:
    ScheduleRepository();
    ~ScheduleRepository();

    std::vector<model::ScheduleModel> getSchedules();

private:
    sqlite::database* _db{nullptr};
};

}

#endif // SCHEDULEREPOSITORY_H
