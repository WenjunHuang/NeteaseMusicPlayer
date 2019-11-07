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
include(DownloadProject.cmake)

download_project(PROJ                fruit
        GIT_REPOSITORY      https://github.com/google/fruit.git
        GIT_TAG             v3.4.0
        GIT_SHALLOW
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )
#download_project(PROJ                catch2
#        GIT_REPOSITORY      https://github.com/catchorg/Catch2.git
#        GIT_TAG             v2.10.2
#        GIT_SHALLOW
#        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
#        )

add_subdirectory(${fruit_SOURCE_DIR} ${fruit_BINARY_DIR})

add_executable(MusicPlayer main.cpp api/http.h api/crypto.h api/crypto.cc)
target_include_directories(MusicPlayer PRIVATE ${fruit_SOURCE_DIR}/include)
target_link_libraries(MusicPlayer LINK_PRIVATE Qt5::Core Qt5::Network Qt5::Quick fruit)

add_executable(test_crypto test/test_crypto.cc api/crypto.cc api/crypto.h)
target_include_directories(test_crypto PRIVATE catch2)
target_link_libraries(test_crypto Qt5::Core crypto++)