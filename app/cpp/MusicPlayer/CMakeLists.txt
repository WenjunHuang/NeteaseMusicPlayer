
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_INCLUDE_CURRENT_DIR  ON)
list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE})
set(CMAKE_MODULE_PATH ${QT_CMAKE})

find_package(Qt5 REQUIRED Core Network Quick QuickControls2)
find_package(QtAV)
add_compile_definitions(QT_NO_FOREACH)

if (WIN32)
    # use vcpkg
    find_package(cryptopp CONFIG REQUIRED)
    find_package(folly CONFIG REQUIRED)
    find_package(glog CONFIG REQUIRED)
    find_package(ZLIB REQUIRED)
    find_package(Boost REQUIRED)
    set(CRYPTOPP cryptopp-static)
    set(FOLLY Folly::folly Folly::folly_deps)
    set(GLOG glog::glog)
    set(BOOST Boost)
    add_compile_options("/Zc:__cplusplus")
    #    add_library(cryptopp ALIAS cryptopp-static)
endif ()
if (APPLE)
    find_package(PkgConfig)
    #    find_package(Boost REQUIRED COMPONENTS container)
    pkg_search_module(cryptopp REQUIRED libcryptopp IMPORTED_TARGET)
    pkg_search_module(folly REQUIRED libfolly IMPORTED_TARGET)
    pkg_search_module(glog REQUIRED libglog IMPORTED_TARGET)
    find_package(Boost REQUIRED)

    set(CRYPTOPP PkgConfig::cryptopp)
    set(FOLLY PkgConfig::folly)
    set(GLOG PkgConfig::glog)
    set(BOOST Boost)
endif ()

add_subdirectory(util)
add_subdirectory(api)
add_subdirectory(repositories)
add_subdirectory(view_models)
add_subdirectory(services)
add_subdirectory(player)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    find_package(Qt5QuickCompiler)
    qtquick_compiler_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)
else ()
    set(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)
endif ()

add_library(application STATIC application.cc application.h )
target_link_libraries(application PUBLIC api util view_models services ${GLOG}
        Qt5::Core
        Qt5::Network
        Qt5::Quick
        Qt5::QuickControls2)

add_executable(MusicPlayer main.cpp ${RESOURCES})
target_link_libraries(MusicPlayer LINK_PRIVATE application)

