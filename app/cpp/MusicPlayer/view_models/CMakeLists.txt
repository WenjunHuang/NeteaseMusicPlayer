add_library(view_models STATIC
        banner_view_model.cc
        personalized_new_song_view_model.cc
        recommendation_song_lists_view_model.cc
        song_category_list_view_model.cc song_category_list_view_model.h)
target_link_libraries(view_models PUBLIC Qt5::Core Qt5::Quick api util repositories)

