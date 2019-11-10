TEMPLATE = app
TARGET = dev

QT += quick quickcontrols2 widgets

RESOURCES += \
    discover_music/personalized/Personalized.qml \
    discover_music/personalized/BannerCarousel.qml \
    discover_music/personalized/RecommendationSongLists.qml \
    discover_music/personalized/PersonalizedNewSongs.qml \
    discover_music/DiscoverMusic.qml \
    MusicPlayer/Button.qml \
    MusicPlayer/Panel.qml \
    utils/Border.qml \
    utils/RoundCorner.qml \
    MusicPlayer/TabBar.qml \
    MusicPlayer/TabButton.qml \
    octicons/Octicon.qml \
    styles/variables.mjs \
    styles/color_system.mjs\
    main.qml


INSTALLS += target
