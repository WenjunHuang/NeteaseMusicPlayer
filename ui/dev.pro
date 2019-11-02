TEMPLATE = app
TARGET = dev

QT += quick quickcontrols2 widgets

RESOURCES += \
    discover_music/BannerCarousel.qml \
    discover_music/RecommendationSongLists.qml \
    MusicPlayer/Button.qml \
    MusicPlayer/Panel.qml \
    octicons/Octicon.qml \
    styles/variables.mjs \
    styles/color_system.mjs\
    main.qml

INSTALLS += target
