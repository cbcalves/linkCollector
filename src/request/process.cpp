#include "process.h"

namespace {

char constexpr START[] = R"-(<script id="__NEXT_DATA__" type="application/json" crossorigin="anonymous">)-";
char constexpr END[] = R"-(</script>)-";
size_t constexpr START_SIZE = sizeof(START) / sizeof(START[0]);

}

namespace request {

nlohmann::json process(std::string const& data) {
    size_t start = data.find(START, 0);
    if (start == std::string::npos) {
        return {};
    }

    size_t end = data.find(END, start);
    if (end == std::string::npos) {
        return {};
    }

    start += START_SIZE - 1;
    end -= start;

    std::string const jsonData = data.substr(start, end);

    return nlohmann::json::parse(jsonData);
}

std::vector<model::LinkModel> getYoutubeLinks(nlohmann::json const& json) {
    if (json.empty()) {
        return {};
    }

    std::vector<model::LinkModel> links{};

    auto jsonLinks = json["props"]["pageProps"]["links"];
    for (auto const& jsonLink : jsonLinks) {
        std::string url = jsonLink["url"];
        if (url.find("youtube") != std::string::npos) {
            links.emplace_back(jsonLink["title"], url);
        }
    }

    return links;
}

}
