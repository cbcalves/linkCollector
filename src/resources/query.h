#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>

namespace query {

std::vector<std::pair<int, std::string>> migrations();
std::string insert_migrations();
std::string find_migrations();

std::string insert_links();

std::string find_schedule();

};

#endif // QUERY_H
