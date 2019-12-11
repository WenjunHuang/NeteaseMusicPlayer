add_library(player STATIC player.cc)
target_link_libraries(player PUBLIC Qt5::Core Qt5::Quick QtAV api util repositories )

