cmake_minimum_required(VERSION 3.15)
project(MusicPlayer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_PREFIX_PATH $ENV{QT_CMAKE})
find_package(PkgConfig)
find_package(Qt5 REQUIRED Core Network Quick)
pkg_search_module(cryptopp REQUIRED libcrypto++)
include(DownloadProject.cmake)

download_project(PROJ fruit
        GIT_REPOSITORY https://github.com/google/fruit.git
        GIT_TAG v3.4.0
        GIT_SHALLOW
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
#download_project(PROJ                RxCpp
#        GIT_REPOSITORY      https://github.com/ReactiveX/RxCpp.git
#        GIT_TAG             v4.1.0
#        GIT_SHALLOW
#        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
#        )

add_subdirectory(${fruit_SOURCE_DIR} ${fruit_BINARY_DIR})
#add_subdirectory(${RxCpp_SOURCE_DIR} ${RxCpp_BINARY_DIR})

add_executable(MusicPlayer MusicPlayer/main.cpp
        MusicPlayer/json.h
        MusicPlayer/api/http.h
        MusicPlayer/api/api.h
        MusicPlayer/api/api.cc
        MusicPlayer/api/crypto.h
        MusicPlayer/api/crypto.cc
        MusicPlayer/api/data/error.h
        MusicPlayer/api/data/dj_banner.h
        MusicPlayer/asyncfuture.h)
target_include_directories(MusicPlayer PRIVATE "${fruit_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/MusicPlayer")
target_link_libraries(MusicPlayer LINK_PRIVATE Qt5::Core Qt5::Network Qt5::Quick fruit)

add_executable(test_crypto test/test_crypto.cc MusicPlayer/api/crypto.cc MusicPlayer/api/crypto.h)
target_include_directories(test_crypto PRIVATE catch2)
target_link_libraries(test_crypto Qt5::Core crypto++)