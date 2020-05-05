add_library(repositories STATIC
        database_repository.cc
        database_response.cc
        image_provider.cc
        database_repository.h tables.h app_config.cc app_config.h)
target_link_libraries(repositories PUBLIC Qt5::Core Qt5::Concurrent SQLITE3 util api)
target_include_directories(repositories INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

