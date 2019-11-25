cmake_minimum_required(VERSION 3.12)
project(MusicPlayer)

#find_path(WASTORAGE_INCLUDE_DIR was/blob.h)
#find_library(WASTORAGE_LIBRARY wastorage)
#message(${WASTORAGE_INCLUDE_DIR})
add_subdirectory(app/cpp/MusicPlayer)
add_subdirectory(app/cpp/test)
