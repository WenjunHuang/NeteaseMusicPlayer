add_library(util STATIC
        json.cc
        logger.cc
        misc.cc
        )
#target_include_directories(util PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(util PUBLIC Qt5::Core)

