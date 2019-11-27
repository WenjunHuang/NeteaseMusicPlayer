add_library(repositories STATIC song_category_repository.cc song_category_repository.h)
target_link_libraries(repositories PUBLIC Qt5::Core Qt5::Network Qt5::Quick  ${FOLLY} util api)


