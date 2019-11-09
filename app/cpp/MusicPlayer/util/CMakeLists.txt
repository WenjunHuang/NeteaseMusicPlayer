add_library(util STATIC
        json.cc)
target_link_libraries(util PUBLIC Qt5::Core)

