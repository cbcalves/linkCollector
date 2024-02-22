#include "migrate.h"

#include <regex>
#include <set>
#include <sqlite_modern_cpp.h>

#include "resources/query.h"

namespace migrate {

Migrate::Migrate() :
    _db{new sqlite::database("linkCollector.db")} { }

Migrate::~Migrate() {
    delete _db;
}

bool Migrate::update() {
    std::vector<std::pair<int, std::string>> const migrations{query::migrations()};

    std::set<int> const migrated{load()};
    for (auto& [id, sql] : migrations) {
        if (migrated.contains(id)) {
            continue;
        }

        try {
            (*_db) << "begin;";
            query(sql);
            save(id);
            (*_db) << "commit;";
        } catch (sqlite::sqlite_exception const& e) {
            (*_db) << "rollback;";
            fprintf(stderr, "Failed to migrate [%s][%d][%d]\nSQL[%s]\n", e.what(), e.get_code(), e.get_extended_code(), e.get_sql().c_str());
            return false;
        }
    }

    return true;
}

std::set<int> Migrate::load() {
    std::string sql = query::find_migrations();

    std::set<int> ids{};

    try {
        for (auto&& row : (*_db) << sql) {
            int id{};
            row >> id;
            ids.insert(id);
        }
    } catch (...) {
        // There is no select before the schema creation
    }

    return ids;
}

void Migrate::save(int id) {
    std::string sql = query::insert_migrations();
    (*_db) << sql << id;
}

void Migrate::query(std::string const& sql) {
    static std::regex const rgx{R"-(;)-"};

    std::string nsql = normalizeQuery(sql);
    for (std::smatch match; std::regex_search(nsql, match, rgx); nsql = match.suffix()) {
        std::string newSql{match.prefix().str() + ';'};
        (*_db) << newSql;
    }
}

std::string Migrate::normalizeQuery(std::string const& sql) {
    static std::regex const rgx(R"--(\n|(\s+))--");
    return std::regex_replace(sql, rgx, " ");
}

}
