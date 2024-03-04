cmake_minimum_required(VERSION 3.27)

project(linkCollector LANGUAGES CXX)

option(ENABLE_TEST "Build with tests." OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(POLICY CMP0135)
    # avoid nlohmann_json warning
    cmake_policy(SET CMP0135 NEW)
endif()

find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(nlohmann_json 3.11.3 QUIET)

if(NOT ${nlohmann_json_FOUND})
    message("-- FetchContent nlohmann_json")
    include(FetchContent)
    FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
    FetchContent_MakeAvailable(json)
endif()

include_directories(external/sqlite_modern_cpp/hdr)
include_directories(src)

add_subdirectory(external/spdlog)

add_library(linkCollectorLib
    src/datetime/date.h
    src/datetime/date.cpp
    src/datetime/datetime.h
    src/datetime/datetime.cpp
    src/datetime/time.h
    src/datetime/time.cpp
    src/eventloop/eventitem.h
    src/eventloop/eventloop.h
    src/eventloop/eventloop.cpp
    src/migrate/migrate.h
    src/migrate/migrate.cpp
    src/model/linkmodel.h
    src/model/linkmodel.cpp
    src/model/schedulemodel.h
    src/model/schedulemodel.cpp
    src/request/request.h
    src/request/request.cpp
    src/request/process.h
    src/request/process.cpp
    src/resources/query.h
    src/resources/query.cpp
    src/signal/signalhandler.h
    src/signal/signalhandler.cpp
)

target_link_libraries(linkCollectorLib
    CURL::libcurl
    nlohmann_json::nlohmann_json
    SQLite::SQLite3
    spdlog
)

if (ENABLE_TEST)
    add_subdirectory(tests)
endif()

include(GNUInstallDirs)
install(TARGETS linkCollector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
