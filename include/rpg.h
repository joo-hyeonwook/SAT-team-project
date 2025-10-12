#pragma once//include 시 #include "../include/rpg.h" 사용할 것(상대경로)
class GameManager {
    public: 
    int map[5][5] = {0, };//맵 배열 생성
    void printMap(int map[5][5]);//맵 출력 함수
    int getExit(int map[5][5]);//배열 인덱스의 주소 반환
    int getDice();//주사위 함수
    void ifBattleStart();
    void battle();
    void gameOver();
    void gameClear();
};
class Character {
    int *location;//배열 인덱스의 주소 
    int hp;//05 고정
    int atk;//10 고정
    int def;//100 고정
    int attack(int atk, int hp);//hp = 상대방 체력
    int defend(int def, int hp);//hp = 상대방 체력

};
class Player : Character {
    int fitstLocation();
    int getLocation(int *location);//배열 인덱스의 주소 반환
    int move(int *location);//배열 인덱스의 주소 반환
    void getPlayerAction(); //플레이어 행동 선택
    void run();
};
class Enemy : Character {
    int makeLocaiotn ();//배열 인덱스의 주소 반환
    void getEnemyAction(); //적 행동 선택
};