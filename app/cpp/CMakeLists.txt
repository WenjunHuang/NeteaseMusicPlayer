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
pkg_search_module(cryptopp REQUIRED libcrypto++)
include(DownloadProject.cmake)


add_subdirectory(MusicPlayer)
add_subdirectory(test)

#add_executable(test_crypto test/test_crypto.cc)
#target_include_directories(test_crypto PRIVATE catch2)
#target_link_libraries(test_crypto PRIVATE api)
