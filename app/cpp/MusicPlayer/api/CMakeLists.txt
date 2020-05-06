add_library(api STATIC
        api.h
        api.cc
        http.h
        http.cc
        music_api.h
        music_api.cc
        crypto.h
        crypto.cc
        api_response.cc
        data/data.h
        error.h
        error.cc
        data/dj_banner.h
        data/dj_category_excludehot.h
        data/dj_category_recommend.h
        data/personalized_newsong.h
        data/user_private_message.h
        data/playlist_catlist.h
        data/banner.cc
        data/dj_banner.cc
        data/dj_category_excludehot.cc
        data/dj_category_recommend.cc
        data/personalized.cc
        data/personalized_newsong.cc
        data/playlist_catlist.cc
        data/song_privilege.cc
        data/user_login.cc
        data/user_private_message.cc
        data/user_private_message.h
        data/playlist_catlist.h
        data/top_playlist.cc
        data/top_playlist.h
        data/playlist_detail.h
        data/playlist_detail.cc
        data/dj_catlist.h
        data/dj_catlist.cc
        data/lyric.cc
        data/lyric.h
        data/song_url.cc
        data/song_url.h)
target_link_libraries(api PUBLIC util Qt5::Core Qt5::Network Qt5::Quick CRYPTOPP)
target_include_directories(api INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

