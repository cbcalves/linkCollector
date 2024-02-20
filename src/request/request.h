#ifndef REQUEST_H
#define REQUEST_H

#include <optional>
#include <string>

namespace request {

std::optional<std::string> request(std::string const& url);

}

#endif // REQUEST_H
