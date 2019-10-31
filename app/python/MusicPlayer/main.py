import os

from MusicPlayer.bootstrap import Bootstrap
from MusicPlayer.run_app import run_app

if __name__ == '__main__':
    run_app(Bootstrap, os.path.join(os.getcwd(), "config"))
