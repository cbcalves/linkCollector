enable_testing()

include(FetchContent)
message("-- FetchContent googletest")
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(
    linkCollectorTests
    datetest.cpp
    timetest.cpp
    datetimetest.cpp

)

target_link_libraries(
    linkCollectorTests
    GTest::gtest_main
    linkCollectorLib
)

include(GoogleTest)
gtest_discover_tests(linkCollectorTests)
