#ifndef PROCESS_H
#define PROCESS_H

#include <nlohmann/json.hpp>

#include "model/linkmodel.h"

namespace request {

nlohmann::json process(std::string const& data);
std::vector<model::LinkModel> getYoutubeLinks(nlohmann::json const& json);

}
#endif // PROCESS_H
