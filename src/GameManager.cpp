#include <iostream>
#include <cstdlib>
#include <random>
#include "../include/rpg.h"

void printmap(int *playerLocation, int *exit) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std:: cout << "[";
            if ( ) {//player 위치
                std:: cout << "P";
            } else if ( ) {//exit 위치
                std:: cout << "E";
            } else {
                std:: cout << " ";//빈공간
            }
            std:: cout << "]";
        }
    }
}

int getDice() {
    std::random_device rd;                         // 하드웨어 기반 시드
    std::mt19937 gen(rd());                        // Mersenne Twister 엔진
    std::uniform_int_distribution<int> dist(1, 100); // 1~100 사이 정수 생성
    int num1 = dist(gen) % 6 + 1;
    int num2 = dist(gen) % 6 + 1;
    return num1 + num2;
}
}
 bool ifBattleStart() {
    printmap();
    if(Player.location == Enemy.location) {
        return true;
    }
    else {
        return false;
    }
 }
    void battle() {
        std::cout<< "전투 시작" << endl;
        while(1) {
            getPlayerAction();
            if()
            getEnemyAction();

        }
    }
    void gameOver();
    void gameClear();