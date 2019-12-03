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
        discover_music/song_list/song_list_high_quality_view_model.h
        discover_music/song_list/song_list_high_quality_view_model.cc
        )
target_link_libraries(view_models PUBLIC Qt5::Core Qt5::Quick api util repositories)

