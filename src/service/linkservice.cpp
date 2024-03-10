#include "linkservice.h"

#include <spdlog/spdlog.h>
#include <sqlite_modern_cpp.h>

#include "request/process.h"
#include "request/request.h"

namespace service {

bool LinkService::process(const model::ScheduleModel& schedule) {
    model::LinkModel lastLink = _repository.getLastLink(schedule.idSchedule());

    if (lastLink.dtCreated() > schedule.dtEvent()) {
        return true;
    }
    spdlog::info("{} [idSchedule]{}", __PRETTY_FUNCTION__, schedule.idSchedule());

    auto links = requestLinks(schedule.url());
    if (!links.has_value()) {
        spdlog::warn("{} no links", __PRETTY_FUNCTION__);
        return false;
    }

    for (auto& link : links.value()) {
        link.setIdSchedule(schedule.idSchedule());
        save(link);
    }

    spdlog::info("{} [links.size]{}", __PRETTY_FUNCTION__, links->size());
    return !links->empty();
}

std::optional<std::vector<model::LinkModel>> LinkService::requestLinks(const std::string& url) {
    spdlog::info("{} [URL] {}", __PRETTY_FUNCTION__, url);

    auto response = request::request(url);
    if (!response.has_value()) {
        spdlog::warn("{} no return", __PRETTY_FUNCTION__);
        return {};
    }

    spdlog::info("{} process", __PRETTY_FUNCTION__);
    auto json = request::process(response.value());
    return request::getYoutubeLinks(json);
}

void LinkService::save(model::LinkModel const& link) {
    try {
        _repository.save(link);
    } catch (...) {
        spdlog::critical("{} error saving [idSchedule]{} [url]{}", __PRETTY_FUNCTION__, link.idSchedule(), link.url());
    }
}

}
