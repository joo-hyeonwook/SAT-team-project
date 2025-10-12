#include <iostream>
#include<cstdlib>
#include<ctime>
#include "../include/rpg.h"


GameManager printmap(int *playerLocation, int *exit) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std:: cout << "[";
            if ( ) {//player 위치
                std:: cout << "P";
            } else if ( ) {//exit 위치
                std:: cout << "E";
            } else {
                std:: cout << " ";//빈공간
            }
            std:: cout << "]";
        }
    }
}

GameManager dice() {
    srand((unsigned int)time(NULL));
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}
