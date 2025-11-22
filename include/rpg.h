#pragma once//include 시 #include "../include/rpg.h" 사용할 것(상대경로)

class Character {
    protected:
    int locationX, locationY;//배열 인덱스의 주소 
    int hp;//05 고정
    int atk;//10 고정
    int def;//100 고정
    public:
    Character();
    int getLocationX() {return this->locationX;}
    int getLocationY() {return this->locationY;}
    int getHp() {return this->hp;}//hp 리턴
    int getAtk() {return this->atk;}
    int getDef() {return this->def;}
    void setAtk(int newAtk);
    void setDef(int newDef);
    void setHp(int atk = 10, int def = 100);//hp 수정 후 리턴

};
class Player : public Character {
    public:
    int getPlayerAction(); //플레이어 행동 선택
    void playerAttack(Enemy& refEnemy, int enemyDef);
    void playerDefend();
    bool run();
};
class Enemy : public Character {
    public:
    int getEnemyAction(); //적 행동 무작위 결정
    void enemyAttack(Player& refPlayer, int playerDef);
    void enemyDefend();
};
namespace GameManager {
    void printTutorial();
    void printMap(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC);//맵 출력 함수
    int getDice();//주사위 함수
    bool ifBattleStart(Player& refPlayer, Enemy& refEnemyA, Enemy& refEnemyB, Enemy& refEnemyC);
    void battle(Player &refPlayer, Enemy &refEnemy);
    void gameOver();
    void ifGameClear(Player &refPlayer);
    void gameClear();
}