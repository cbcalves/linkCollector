#ifndef LINKREPOSITORY_H
#define LINKREPOSITORY_H

#include "model/linkmodel.h"

namespace sqlite {
class database;
}

namespace repository {

class LinkRepository {
public:
    LinkRepository();
    ~LinkRepository();

    model::LinkModel getLastLink(const int idSchedule);
    void save(model::LinkModel const& link);

private:
    sqlite::database* _db{nullptr};
};

}

#endif // LINKREPOSITORY_H
