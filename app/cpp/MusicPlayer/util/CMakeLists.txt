add_library(util STATIC
        util.h
        util.cc
        json.cc
        logger.cc
        misc.cc
        executor.cc
        wobjectcpp.h
        wobjectdefs.h
        wobjectimpl.h)
#target_include_directories(util PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(util PUBLIC Qt5::Core)
target_include_directories(util INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)