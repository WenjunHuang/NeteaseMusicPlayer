
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_MAP_IMPORTED_CONFIG_MINSIZEREL Release)
set(CMAKE_MAP_IMPORTED_CONFIG_RELWITHDEBINFO Release)
list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE})
set(CMAKE_MODULE_PATH ${QT_CMAKE})

find_package(QtAV REQUIRED)
find_package(Qt5 REQUIRED Core Network Quick QuickControls2)
add_compile_definitions(QT_NO_FOREACH)

if (MSVC)
    # use vcpkg
    find_package(cryptopp CONFIG REQUIRED)
    find_package(folly CONFIG REQUIRED)
    find_package(glog CONFIG REQUIRED)
    find_package(ZLIB REQUIRED)
    find_package(sqlite3 CONFIG REQUIRED)


    # add interface targets
    add_library(CRYPTOPP INTERFACE)
    target_link_libraries(CRYPTOPP INTERFACE cryptopp-static)
    add_library(FOLLY INTERFACE)
    target_link_libraries(FOLLY INTERFACE Folly::folly Folly::folly_deps)
    add_library(GLOG INTERFACE)
    target_link_libraries(GLOG INTERFACE glog::glog)
    add_library(SQLITE3 INTERFACE)
    target_link_libraries(SQLITE3 INTERFACE sqlite3)

    # make visual c++ to treat every source file with utf-8 encoding instead of utf8-bom
    add_compile_options("/Zc:__cplusplus" "/utf-8")
endif ()
if (APPLE)
    find_package(PkgConfig)
    #    find_package(Boost REQUIRED COMPONENTS container)
    pkg_search_module(cryptopp REQUIRED libcryptopp IMPORTED_TARGET)
    pkg_search_module(folly REQUIRED libfolly IMPORTED_TARGET)
    pkg_search_module(glog REQUIRED libglog IMPORTED_TARGET)
    find_package(Boost REQUIRED)

    # add interface targets
    add_library(CRYPTOPP INTERFACE)
    target_link_libraries(CRYPTOPP INTERFACE PkgConfig::cryptopp)
    add_library(FOLLY INTERFACE)
    target_link_libraries(FOLLY INTERFACE PkgConfig::folly)
    add_library(GLOG INTERFACE)
    target_link_libraries(GLOG INTERFACE PkgConfig::glog)
    add_library(SQLITE3 INTERFACE)
    target_link_libraries(SQLITE3 INTERFACE sqlite3)
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

add_library(application STATIC application.h application.cc)
target_link_libraries(application PUBLIC api util view_models services player
        Qt5::Core
        Qt5::Network
        Qt5::Quick
        Qt5::QuickControls2)

add_executable(MusicPlayer main.cc ${RESOURCES})
target_link_libraries(MusicPlayer PRIVATE application)
target_compile_definitions(MusicPlayer PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

#add_executable(MusicPlayer main.cpp ${RESOURCES})
#target_link_libraries(MusicPlayer PRIVATE application)

