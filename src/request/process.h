#ifndef PROCESS_H
#define PROCESS_H

#include <nlohmann/json.hpp>

namespace request {

struct Link {
    std::string title{};
    std::string url{};
};

nlohmann::json process(std::string const& data);
std::vector<Link> getYoutubeLinks(nlohmann::json const& json);

}
#endif // PROCESS_H
