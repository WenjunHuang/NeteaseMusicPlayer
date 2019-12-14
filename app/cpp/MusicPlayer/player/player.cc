#include "player.h"

namespace MusicPlayer::Player {
   Player* Player::_instance = nullptr;

   Player::Player() {
     _avPlayer = new QtAV::AVPlayer(this);
   }

   void Player::initInstance() {
     if (_instance == nullptr){
       _instance = new Player;
     }
   }

   Player* Player::instance(){
     return _instance;
   }

   void Player::freeInstance() {
     if (_instance){
       delete _instance;
       _instance = nullptr;
     }
   }
   void Player::play(QString songUrl) {
       _avPlayer->play(songUrl);
   }
}