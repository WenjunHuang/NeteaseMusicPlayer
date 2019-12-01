add_library(view_models STATIC
        view_models.cc
        banner_view_model.cc
        personalized_new_song_view_model.cc
        recommendation_song_lists_view_model.cc
        song_category_list_view_model.cc
        song_category_list_view_model.h song_list_high_quality_view_model.cc song_list_high_quality_view_model.h states.h states.cc)
target_link_libraries(view_models PUBLIC Qt5::Core Qt5::Quick api util repositories)

