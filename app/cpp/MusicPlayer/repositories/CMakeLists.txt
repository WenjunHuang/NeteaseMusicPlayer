if (WIN32)
    find_package(sqlite3 CONFIG REQUIRED)
endif ()
if (APPLE)
endif ()
add_library(repositories STATIC
        database_repository.cc database_repository.h tables.h)
target_link_libraries(repositories PUBLIC Qt5::Core Qt5::Network Qt5::Quick ${FOLLY} sqlite3 util api)


