
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE})


find_package(Qt5 REQUIRED Core Network Quick QuickControls2)
find_package(Qt5QuickCompiler)
add_compile_definitions(QT_NO_FOREACH)

if (WIN32)
    # use vcpkg
    find_package(cryptopp CONFIG REQUIRED)
    find_package(folly CONFIG REQUIRED)
    find_package(glog CONFIG REQUIRED)
    set(CRYPTOPP cryptopp-static)
    set(FOLLY folly-static)
    set(GLOG glog-static)
    #    add_library(cryptopp ALIAS cryptopp-static)
endif ()
if (APPLE)
    find_package(PkgConfig)
#    find_package(Boost REQUIRED COMPONENTS container)
    pkg_search_module(cryptopp REQUIRED libcryptopp IMPORTED_TARGET)
    pkg_search_module(folly REQUIRED libfolly IMPORTED_TARGET)
    pkg_search_module(glog REQUIRED libglog IMPORTED_TARGET)
    set(CRYPTOPP PkgConfig::cryptopp)
    set(FOLLY PkgConfig::folly)
    set(GLOG PkgConfig::glog)
endif ()

add_subdirectory(util)
add_subdirectory(api)
add_subdirectory(view_models)
add_subdirectory(repositories)

if (CMAKE_BUILD_TYPE EQUAL "Release")
    qtquick_compiler_add_resources(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)
else ()
    set(RESOURCES ${CMAKE_SOURCE_DIR}/resources.qrc)
endif ()

add_executable(MusicPlayer main.cpp application.cc ${RESOURCES})
target_link_libraries(MusicPlayer LINK_PRIVATE api util view_models
        ${GLOG}
        Qt5::Core
        Qt5::Network
        Qt5::Quick
        Qt5::QuickControls2)

