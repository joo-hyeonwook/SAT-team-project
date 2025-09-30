class GameManager {
    public: 
    int map[5][5];//맵 배열
    int printMap(int map[5][5]);//맵 출력 함수
    int *exit(int map[5][5]);//배열 인덱스의 주소 반환
    int dice();//주사위 함수
    void battleStart();
    void battle();
    void battleEnd();
    void gameOver();
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
    int fitstLocation(int *location);
    int move(int *location);//배열 인덱스의 주소 반환
    void run();
};
class Enemy1 : Character {
    int makeLocaiotn (int *location);//배열 인덱스의 주소 반환
};