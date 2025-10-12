#include <iostream>
#include "../include/rpg.h"

int main() {
    GameManager manager;
    Player player;
    Enemy enemy[3];

    player.fitstLocation();
    for (int i = 0; i < 3; i++) {
        enemy[i].makeLocaiotn();
    }
    while(1) {
        manager.printMap(manager.map);
        while(1) {
            player.move(player.getLocation());
            if (manager.ifBattleStart == true) {
                manager.battle();
            } 
        }
    }
    return 0;
}