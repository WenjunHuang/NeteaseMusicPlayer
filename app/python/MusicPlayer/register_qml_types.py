from PyQt5.QtQml import qmlRegisterType

from MusicPlayer.view_models.banner_view_model.view_model import BannerViewModel


def register_qml_types():
    qmlRegisterType(BannerViewModel, "MusicPlayer", 1, 0, BannerViewModel.__name__)
    # qmlRegisterType(SignInViewModel, "Desktop", 1, 0, SignInViewModel.__name__)
    # qmlRegisterType(ChangesViewModel, "Desktop", 1, 0, ChangesViewModel.__name__)
