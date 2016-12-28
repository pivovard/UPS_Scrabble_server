//
// Created by pivov on 25-Dec-16.
//

#include "Game.h"

Game::Game(int id)
{
    this->id = id;

    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->matrix[i][j] = '*';
        }
    }
}
