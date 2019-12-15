if (WIN32)
    find_package(sqlite3 CONFIG REQUIRED)
endif ()
if (APPLE)
endif ()
add_library(services STATIC
        song_category_repository.cc
        song_category_repository.h
        user_auth.cc user_auth.h play_list_repository.cc play_list_repository.h)
target_link_libraries(services PUBLIC Qt5::Core Qt5::Network Qt5::Quick ${FOLLY} repositories util api)


