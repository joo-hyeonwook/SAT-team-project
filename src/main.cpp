#include <iostream>
#include "../include/rpg.h"

using namespace GameManager;

int main() {
    Player player;
    Enemy enemy[3]; 
    while(1) {
        printMap(player, enemy[0], enemy[1], enemy[2]);
        while(1) {
            player.move();
            ifBattleStart(player, enemy[0], enemy[1], enemy[2]);
        }
        ifGameClear(player);
    }

    return 0;
}