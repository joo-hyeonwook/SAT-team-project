#pragma once//include 시 #include "../include/rpg.h" 사용할 것(상대경로)
class GameManager {
    public: 
    int *getMap();//맵 배열 생성
    void printMap(int map);//맵 출력 함수
    int getExit(int map[5][5]);//배열 인덱스의 주소 반환
    int getDice();//주사위 함수
    bool ifBattleStart(int playerLocation, int enemyLocation);
    void battle(Player &refPlayer, Enemy &refEnemy);
    void gameOver();
    void gameClear();
};
class Character {
    int location;//배열 인덱스의 주소 (map[i][j]라면 location == i*10+j)
    int hp;//05 고정
    int atk;//10 고정
    int def;//100 고정
    public:
    int attack(int myAtk, int opponentHp);//hp = 상대방 체력
    int defend(int myDef, int opponentHp);//hp = 상대방 체력

};
class Player : Character {
    public:
    int fitstLocation();
    int getLocation(int *location);//배열 인덱스의 주소 반환
    int move(int *location);//배열 인덱스의 주소 반환
    int getPlayerAction(); 
    //플레이어 행동 선택(공격출 1, 방어 2, 도망치기 3 중 입력받아 리턴)
    void run();
};
class Enemy : Character {
    public:
    int makeLocaiotn ();//배열 인덱스의 주소 반환
    int getEnemyAction(); //적 행동 무작위 결정 후 리턴(공격1, 방어2)
};