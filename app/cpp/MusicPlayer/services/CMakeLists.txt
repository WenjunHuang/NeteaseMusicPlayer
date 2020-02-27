add_library(services STATIC
        song_category_repository.cc
        song_category_repository.h
        user_auth.cc user_auth.h play_list_repository.cc play_list_repository.h)
target_link_libraries(services PUBLIC Qt5::Core FOLLY repositories util api)
target_include_directories(services INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> PRIVATE ${Boost_INCLUDE_DIRS})


