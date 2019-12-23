add_library(player STATIC player.cc)
target_link_libraries(player PUBLIC Qt5::Core Qt5::Quick  api util repositories)
target_link_libraries(player PUBLIC "${QTAV_LIBRARIES}/QtAV")

