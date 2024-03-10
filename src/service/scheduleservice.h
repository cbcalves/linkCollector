#ifndef SCHEDULESERVICE_H
#define SCHEDULESERVICE_H

#include "model/schedulemodel.h"
#include "repository/schedulerepository.h"

namespace service {

class ScheduleService {
public:
    ScheduleService();

    int exec();

private:
    repository::ScheduleRepository _repository;
};

}

#endif // SCHEDULESERVICE_H
