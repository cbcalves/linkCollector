#ifndef LINKSERVICE_H
#define LINKSERVICE_H

#include "model/schedulemodel.h"
#include "repository/linkrepository.h"

namespace service {

class LinkService {
public:
    bool process(model::ScheduleModel const& schedule);

private:
    repository::LinkRepository _repository;

    std::optional<std::vector<model::LinkModel>> requestLinks(std::string const& url);
    void save(model::LinkModel const& link);
};

}

#endif // LINKSERVICE_H
