#include <iostream>
#include "../include/rpg.h"

int main() {
    GameManager *manager = new GameManager();
    Player *player = new Player();
    Enemy *enemy[] = new Enemy[3]; 

    player.fitstLocation();
    for (int i = 0; i < 3; i++) {
        enemy[i].makeLocaiotn();
    }
    while(1) {
        manager.printMap(manager.map);
        while(1) {
            player.move(player.location);
            if (manager.ifBattleStart == true) {
                manager.battle();
            } 
        }
    }
    delete manager;
    delete player;
    delete[] enemy;
    return 0;
}