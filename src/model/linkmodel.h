#ifndef LINKMODEL_H
#define LINKMODEL_H

#include <string>

#include "datetime/datetime.h"

namespace model {

class LinkModel {
public:
    LinkModel() = default;
    explicit LinkModel(std::string const& title, std::string const& url);

    std::string title() const;
    void setTitle(std::string const& title);

    std::string url() const;
    void setUrl(std::string const& url);

    datetime::DateTime dtCreated() const;
    void setDtCreated(datetime::DateTime const dtCreated);

    int idLink() const;
    void setIdLink(int idLink);

    int idSchedule() const;
    void setIdSchedule(int idSchedule);

private:
    std::string _title{};
    std::string _url{};
    datetime::DateTime _dtCreated{};
    int _idLink{};
    int _idSchedule{};
};

}

#endif // LINKMODEL_H
