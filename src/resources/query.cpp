#include "query.h"

namespace query {

std::string databseName() {
    static std::string name = R"-(linkCollector.db)-";
    return name;
}

std::vector<std::pair<int, std::string>> migrations() {
    return {
        {1, R"-(
DROP TABLE IF EXISTS migrate;
CREATE TABLE migrate (
    id INTEGER NOT NULL UNIQUE,
    dtcreated DATETIME NOT NULL
);
)-"},
        {2, R"-(
DROP TABLE IF EXISTS links;
CREATE TABLE links (
    idlink INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
    idschedule INTEGER NOT NULL,
    title TEXT NOT NULL,
    url TEXT NOT NULL UNIQUE,
    dtcreated DATETIME NOT NULL
);
)-"},
        {3, R"-(
DROP TABLE IF EXISTS schedule;
CREATE TABLE schedule (
    idschedule INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,
    title TEXT,
    url TEXT,
    dtevent DATETIME,
    nrweekday INTEGER,
    timestart VARCHAR(8)
);
)-"},
    };
}

std::string insert_migrations() {
    static std::string insert = R"-(INSERT INTO migrate (id, dtcreated) VALUES (?, DATETIME('now', 'localtime'));)-";
    return insert;
}

std::string find_migrations() {
    static std::string find = R"-(SELECT id FROM migrate;)-";
    return find;
}

std::string insert_links() {
    static std::string insert = R"-(INSERT INTO links (idschedule, title, url, dtcreated) VALUES (?, ?, ?, DATETIME('now', 'localtime'));)-";
    return insert;
}

std::string find_last_link() {
    static std::string insert = R"-(SELECT idlink, idschedule, title, url, dtcreated FROM links WHERE idschedule = ? ORDER BY dtcreated DESC LIMIT 1;)-";
    return insert;
}

std::string find_schedule() {
    static std::string find = R"-(SELECT idschedule, title, url, dtevent, nrweekday, timestart FROM schedule;)-";
    return find;
}

}
