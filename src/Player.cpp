#include <iostream>
#include "../include/rpg.h"

using namespace GameManager;

int Player::move(int *location) {//배열 인덱스의 주소 반환

}
int Player::getPlayerAction() {
    int action;
    while (true) {
        std::cout << "\n행동 입력 (1:공격, 2:방어, 3:도망): ";
        std::cin >> action;
        if ((action == 1)||(action == 2)||(action == 3)) {
            return action;
        }
        else {
            return 0;
        }
    }
} //플레이어 행동 선택
void Player::playerAttack(Enemy& refEnemy, int enemyDef) {
    std::cout << "플레이어가 공격했다!\n";
    int dice = getDice();
    if (dice < 5) {
        std::cout << "실패!\n";
        refEnemy.setHp(0, enemyDef);
    }
    else if (dice < 9) {
        std::cout << "성공!\n";
        refEnemy.setHp(atk, enemyDef);
    }
    else {
        std::cout << "대성공!\n";
        refEnemy.setHp(atk * 2, enemyDef);
    }
}
void Player::playerDefend() {
    std::cout << "플레이어가 방어했다!\n";
    int dice = getDice();
    if (dice < 5) {
        std::cout << "실패! (방어율 0%)\n";
        this->def = 0;
    }
    else if (dice < 9) {
        std::cout << "성공! (방어율 50%)\n";
        this->def = 50;
    }
    else {
        std::cout << "대성공! (방어율 100%)\n";
        this->def = 100;
    }
}
bool Player::run() {
    int dice = getDice();
    if (dice <= 7) {
        return false;
    }
    else {
        return true;
    }
}