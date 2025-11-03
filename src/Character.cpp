#include <iostream>
#include "../include/rpg.h"

using namespace GameManager;

Character::Character() {
    this->hp = 50;
    this->atk = 10;
    this->def = 100;
}
void Character::setHp(int atk, int def) {
    this->hp = this->hp - atk*(def/100);
}
int Character::getHp() {
    return this->hp;
}
int attack(int myAtk, Character opponent) {//hp = 상대방 체력
    if (getDice() < 5) {
        opponent.setHp(myAtk*0);
    }
    else if(getDice() < 9) {
        opponent.setHp(myAtk);
    }
    else {
        opponent.setHp(myAtk*2);
    }
}
int defend(Character opponent) {//hp = 상대방 체력

}