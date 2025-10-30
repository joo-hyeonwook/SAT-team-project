#include <iostream>
#include "../include/rpg.h"

int main() {
    int *map = getMap();
    Player player;
    Enemy enemy[3]; 

    player.fitstLocation();
    for (int i = 0; i < 3; i++) {
        enemy[i].makeLocaiotn();
    }
    while(1) {
        printMap(map);
        while(1) {
            player.move(player.location);
            if (ifBattleStart == true) {
                battle();
            } 
        }
    }
    delete map;
    return 0;
}