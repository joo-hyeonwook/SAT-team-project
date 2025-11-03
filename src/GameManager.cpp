#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include "../include/rpg.h"

int* getMap() {
    int* arr = new int[5 * 5]; // 동적 메모리
    for (int i = 0; i < 25; i++)
        arr[i] = 0; // 예시로 값 초기화
    return arr;     // OK (스택에서 안 사라짐)
}
int* getStart(int map[5][5]) {
    return &map[0][0];
}
int* getExit(int map[5][5]) {
    return &map[4][4];
}
void printmap(int playerLocation, int enemyLocation, int *exit) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std:: cout << "[";
            if ((i*10+j) == playerLocation ) {//player 위치
                std:: cout << "P";
            } else if ((i*10+j) == enemyLocation ) {//exit 위치
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

bool ifBattleStart(int playerLocation, int enemyLocation) {
    if(playerLocation == enemyLocation) {
        return true;
    }
    else {
        return false;
    }
}
void battle(Player &refPlayer, Enemy &refEnemy) {
        std::cout<< "전투 시작" << std::endl;
        while(1) {
            int playerAction = refPlayer.getPlayerAction();
            if (playerAction == 1) {
                refPlayer.attack(refEnemy);
            }
            else if(playerAction == 2) {
                refPlayer.defend(refEnemy);
            }
            else if(playerAction == 3) {
                refPlayer.run(); 
            }
            if (refEnemy.getHp() == 0) {
                break;
            }
            
            int enemyAction = refEnemy.getEnemyAction();
            
            if ( enemyAction == 1) {

            }
            else if( enemyAction == 2) {

            }
            if (refPlayer.getHp() == 0) {
                gameOver();
            }

        }
    }
    void gameOver() {
        std::cout << "Game Over";
        for (int i = 5; i > 0; --i) {
            std::cout << i << "초 후 게임 종료" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        exit(1);
    }
    void gameClear() {
        std::cout << "Game Clear!";
        for (int i = 5; i > 0; --i) {
            std::cout << i << "초 후 게임 종료" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        exit(1);
    }