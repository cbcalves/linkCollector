#include "linkrepository.h"

#include <sqlite_modern_cpp.h>

#include "resources/query.h"

namespace repository {

LinkRepository::LinkRepository() :
    _db{new sqlite::database(query::databseName())} { }

LinkRepository::~LinkRepository() {
    delete _db;
}

model::LinkModel LinkRepository::getLastLink(const int idSchedule) {
    std::string sql = query::find_last_link();
    model::LinkModel link{};

    (*_db) << sql << idSchedule >> [&](int idLink, int idSchedule, std::string const& title, std::string const& url, std::string const& dtCreated) -> void {
        link.setIdLink(idLink);
        link.setIdSchedule(idLink);
        link.setTitle(title);
        link.setUrl(url);
        link.setDtCreated(datetime::DateTime::fromString(dtCreated));
    };

    return link;
}

void LinkRepository::save(const model::LinkModel& link) {
    std::string sql = query::insert_links();
    (*_db) << sql << link.idSchedule() << link.title() << link.url();
}

}
