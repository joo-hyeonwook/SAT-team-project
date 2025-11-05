#include <iostream>
#include <cstdlib>
#include <random>
#include <chrono>
#include <thread>
#include "../include/rpg.h"

void printTutorial() {
    std::cout << "당신은 5X5타일로 이뤄진 맵에서 적들을 물리치며 출구를 찾아야 합니다." << std::endl;
    std::cout << "맵 상에서 플레이어가 위치한 타일은 'P', 출구가 위치한 타일은 'E'로 표시됩니다." << std::endl;
    std::cout << "맵 곳곳에는 보이지 않는 적들이 숨어있습니다. 만약 적이 위치한 타일을 밟게 되면 전투가 시작됩니다." << std::endl;
    std::cout << "전투 시, 당신은 적과 번갈아 행동을 수행하게 됩니다." << std::endl;
    std::cout << "당신은 1, 2, 3 중 하나의 숫자를 입력해 각각 공격, 방어, 도망치기 중 하나의 행동을 수행할 수 있습니다." << std::endl;
    std::cout << "적은 공격 혹은 방어를 무작위로 수행할 수 있습니다." << std::endl;
    std::cout << "행동의 성공 여부는 6면체 주사위를 두 번 굴려 나온 눈금의 합에 의해 결정됩니다." << std::endl;
    std::cout << "공격과 방어는 실패, 성공, 대성공의 결과가, 도망치기는 실패 혹은 성공의 결과를 가질 수 있습니다." << std::endl;
    std::cout << "모든 행동은 실패 시 무효화되어 아무런 효과를 가지지 않습니다." << std::endl;
    std::cout << "공격은 성공 시 10, 대성공 시 20의 피해를 적에게 줄 수 있습니다." << std::endl;
    std::cout << "방어는 성공 시 50%, 대성공 시 100%의 받는 피해량 감소 효과가 부여됩니다." << std::endl;
    std::cout << "도망치기는 성공 시 전투가 즉시 종료됩니다. 하지만 해당 타일에 적이 위치한다는 것은 변함없으므로 동일한 타일을 또 밟게 되면 전투가 시작됩니다. " << std::endl;
    std::cout << "이제 게임이 시작됩니다. 행운을 빕니다!" << std::endl;
}
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