add_library(service STATIC
        user_auth.cc user_auth.h play_list_repository.cc play_list_repository.h service.h service.cc)
target_link_libraries(service PUBLIC Qt5::Core repository util api)
target_include_directories(service INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> PRIVATE ${Boost_INCLUDE_DIRS})


