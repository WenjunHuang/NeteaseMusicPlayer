cmake_minimum_required(VERSION 3.15)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_PREFIX_PATH $ENV{QT_CMAKE})
find_package(PkgConfig)
find_package(Qt5 REQUIRED Core Network Quick Concurrent QuickControls2)
find_package(Qt5QuickCompiler)
find_package(Boost REQUIRED)
pkg_search_module(cryptopp REQUIRED libcrypto++ IMPORTED_TARGET)

qtquick_compiler_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)

add_subdirectory(util)
add_subdirectory(api)
add_subdirectory(view_models)
add_executable(MusicPlayer main.cpp application.cc ${RESOURCES})
target_link_libraries(MusicPlayer LINK_PRIVATE api util view_models
        Qt5::Core
        Qt5::Network
        Qt5::Quick
        Qt5::Concurrent
        Qt5::QuickControls2)

