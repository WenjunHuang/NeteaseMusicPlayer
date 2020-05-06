add_library(view_model STATIC
        view_model.h
        view_model.cc
        states.h
        states.cc
        discover_music/personalized/banner_view_model.h
        discover_music/personalized/banner_view_model.cc
        discover_music/personalized/personalized_new_song_view_model.h
        discover_music/personalized/personalized_new_song_view_model.cc
        discover_music/personalized/recommendation_song_lists_view_model.h
        discover_music/personalized/recommendation_song_lists_view_model.cc
        discover_music/song_list/song_category_list_view_model.h
        discover_music/song_list/song_category_list_view_model.cc
        discover_music/song_list/song_list_high_quality_banner_view_model.h
        discover_music/song_list/song_list_high_quality_banner_view_model.cc
        discover_music/song_list/song_category_play_lists_view_model.cc discover_music/song_list/song_category_play_lists_view_model.h base_state_view_model.cc base_state_view_model.h discover_music/dj/dj_banner_view_model.cc discover_music/dj/dj_banner_view_model.h)
target_link_libraries(view_model PUBLIC Qt5::Core Qt5::Quick api util repository service)
target_include_directories(view_model INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
