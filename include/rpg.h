#pragma once//include 시 #include "../include/rpg.h" 사용할 것(상대경로)

class Character {
    int *location;//배열 인덱스의 주소 
    int hp;//05 고정
    int atk;//10 고정
    int def;//100 고정
    public:
    int getHp() {return this->hp;}//hp 리턴
    int setHp(int atk = 10, int def = 100);//hp 수정 후 리턴

};
class Player : public Character {
    public:
    int getLocation(int *location);//배열 인덱스의 주소 반환
    int move(int *location);//배열 인덱스의 주소 반환
    int getPlayerAction(); //플레이어 행동 선택
    int attack(Enemy& refEnemy);
    int defend(Enemy& refEnemy);
    void run();
};
class Enemy : public Character {
    public:
    int getEnemyAction(); //적 행동 무작위 결정
    int attack(Player& refPlayer);
    int defend(Player& refPlayer);
};
namespace GameManager {
    int* getMap();//맵 생성 함수
    int* getStart(int (*map)[5][5]);
    int* getExit(int (*map)[5][5]);
    void printMap(int (*map)[5][5]);//맵 출력 함수
    int getDice();//주사위 함수
    bool ifBattleStart(int playerLocation, int enemyLocation);
    void battle(Player &refPlayer, Enemy &refEnemy);
    void gameOver();
    void gameClear();
}