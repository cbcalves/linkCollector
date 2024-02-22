#ifndef MIGRATE_H
#define MIGRATE_H

#include <set>
#include <string>

namespace sqlite {
class database;
}

namespace migrate {

class Migrate {
public:
    Migrate();
    ~Migrate();

    bool update();

private:
    sqlite::database* _db{nullptr};
    std::set<int> load();
    void save(int id);
    void query(const std::string &sql);

    std::string normalizeQuery(const std::string &sql);
};

}

#endif // MIGRATE_H
