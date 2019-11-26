
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
list(APPEND CMAKE_PREFIX_PATH ${QT_CMAKE})

find_package(Qt5 REQUIRED Core Network Quick Concurrent QuickControls2)
find_package(Qt5QuickCompiler)

if (WIN32)
    # use vcpkg
    find_package(cryptopp CONFIG REQUIRED)
#    add_library(cryptopp ALIAS cryptopp-static)
else ()
    find_package(PkgConfig)
    find_package(Boost REQUIRED COMPONENTS container)
    pkg_search_module(cryptopp REQUIRED libcryptopp IMPORTED_TARGET)
    set(cryptopp PkgConfig::cryptopp)
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
        Qt5::Core
        Qt5::Network
        Qt5::Quick
        Qt5::Concurrent
        Qt5::QuickControls2)

