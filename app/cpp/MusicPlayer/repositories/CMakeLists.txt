add_library(repositories STATIC
        database_repository.cc database_repository.h tables.h)
target_link_libraries(repositories PUBLIC Qt5::Core FOLLY SQLITE3 util api)
target_include_directories(repositories INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

