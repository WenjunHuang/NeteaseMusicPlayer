add_library(api STATIC
        http.h
        http.cc
        api.h
        api.cc
        crypto.h
        crypto.cc
        data/error.h
        data/dj_banner.h
        data/dj_category_excludehot.h
        data/dj_category_recommend.h
        data/personalized_newsong.h
        )
target_link_libraries(api PUBLIC Qt5::Core Qt5::Network Qt5::Quick Qt5::Concurrent  PkgConfig::cryptopp util)

