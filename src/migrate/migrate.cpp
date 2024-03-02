#include "migrate.h"

#include <regex>
#include <set>
#include <spdlog/spdlog.h>
#include <sqlite_modern_cpp.h>

#include "resources/query.h"

namespace migrate {

Migrate::Migrate() :
    _db{new sqlite::database(query::databseName())} { }

Migrate::~Migrate() {
    delete _db;
}

bool Migrate::update() {
    std::vector<std::pair<int, std::string>> const migrations{query::migrations()};
    spdlog::info("{} [migrations.size]{}", __PRETTY_FUNCTION__, migrations.size());

    std::set<int> const migrated{load()};
    spdlog::info("{} [migrated.size]{}", __PRETTY_FUNCTION__, migrated.size());
    for (auto& [id, sql] : migrations) {
        if (migrated.contains(id)) {
            continue;
        }

        try {
            spdlog::info("{} executing [id]{}", __PRETTY_FUNCTION__, id);

            (*_db) << "begin;";
            query(sql);
            save(id);
            (*_db) << "commit;";
        } catch (sqlite::sqlite_exception const& e) {
            (*_db) << "rollback;";
            spdlog::critical("{} Failed to migrate [{}] [{}] [{}] [{}]", __PRETTY_FUNCTION__, e.what(), e.get_code(), e.get_extended_code(), e.get_sql());
            return false;
        }
    }

    spdlog::info("{} finished", __PRETTY_FUNCTION__);
    return true;
}

std::set<int> Migrate::load() {
    std::string sql = query::find_migrations();

    std::set<int> ids{};

    try {
        (*_db) << sql >> [&](const int id) -> void {
            ids.insert(id);
        };
    } catch (...) {
        spdlog::warn("{} no schema found", __PRETTY_FUNCTION__);
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
