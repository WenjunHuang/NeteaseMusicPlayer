cmake_minimum_required(VERSION 3.15)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_PREFIX_PATH $ENV{QT_CMAKE})
find_package(PkgConfig)
find_package(Qt5 REQUIRED Core Network Quick Concurrent)
pkg_search_module(cryptopp REQUIRED libcrypto++ IMPORTED_TARGET)
pkg_search_module(fruit REQUIRED libfruit IMPORTED_TARGET)

add_subdirectory(util)
add_subdirectory(api)
add_executable(MusicPlayer main.cpp)
target_link_libraries(MusicPlayer LINK_PRIVATE api  PkgConfig::fruit)

