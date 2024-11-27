cmake_minimum_required(VERSION 3.15)

project(BigInt)

find_package(Catch2 3 REQUIRED)



set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(${PROJECT_SOURCE_DIR})
add_library(BigIntLib ${PROJECT_SOURCE_DIR}/operator.cpp ${PROJECT_SOURCE_DIR}/BigInt.cpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE BigIntLib)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
add_executable(tests tests/addition.cpp tests/subtraction.cpp tests/multiplication.cpp)
catch_discover_tests(tests)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/)
target_link_libraries(tests PRIVATE BigIntLib)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

