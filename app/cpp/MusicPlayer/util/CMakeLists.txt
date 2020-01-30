add_library(util STATIC
        json.cc
        logger.cc
        misc.cc
        executor.cc
        executor.h
        cpu_thread_pool_executor.cc
        )
#target_include_directories(util PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(util PUBLIC Qt5::Core ${FOLLY})
target_include_directories(util PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)