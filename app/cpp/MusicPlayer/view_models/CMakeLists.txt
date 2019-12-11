add_library(view_models STATIC
        view_models.h
        view_models.cc
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
target_link_libraries(view_models PUBLIC Qt5::Core Qt5::Quick api util repositories)

