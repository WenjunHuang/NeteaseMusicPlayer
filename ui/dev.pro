TEMPLATE = app
TARGET = dev

QT += quick quickcontrols2 widgets

RESOURCES += \
    discover_music/BannerCarousel.qml \
    discover_music/RecommendationSongLists.qml \
    discover_music/PersonalizedNewSongs.qml \
    MusicPlayer/Button.qml \
    MusicPlayer/Panel.qml \
    MusicPlayer/RoundCorner.qml \
    octicons/Octicon.qml \
    styles/variables.mjs \
    styles/color_system.mjs\
    main.qml

INSTALLS += target
