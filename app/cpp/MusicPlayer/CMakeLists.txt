
set(CMAKE_CXX_STANDARD 20)
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

