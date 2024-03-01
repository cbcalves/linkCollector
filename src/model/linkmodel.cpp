#include "linkmodel.h"

namespace model {

LinkModel::LinkModel(std::string const& title, std::string const& url) :
    _title(title),
    _url(url) { }

std::string LinkModel::title() const {
    return _title;
}

void LinkModel::setTitle(std::string const& title) {
    _title = title;
}

std::string LinkModel::url() const {
    return _url;
}

void LinkModel::setUrl(std::string const& url) {
    _url = url;
}

datetime::DateTime LinkModel::dtCreated() const {
    return _dtCreated;
}

void LinkModel::setDtCreated(datetime::DateTime const dtCreated) {
    _dtCreated = dtCreated;
}

int LinkModel::idLink() const {
    return _idLink;
}

void LinkModel::setIdLink(int idLink) {
    _idLink = idLink;
}

int LinkModel::idSchedule() const {
    return _idSchedule;
}

void LinkModel::setIdSchedule(int idSchedule) {
    _idSchedule = idSchedule;
}

}
