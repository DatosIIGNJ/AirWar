//
// Created by gerardo on 29/03/17.
//

#include "Bala.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

Bala::Bala(int _X, int _Y, int _Pot) {
    BalaX = _X;
    BalaY = _Y;
    Pot = _Pot;
}

void Bala::DisparaNave(){
    BalaY -= 8;
}

ALLEGRO_BITMAP* Bala::Dibujar(char *name){
    ALLEGRO_BITMAP *Skin;
    Skin = al_load_bitmap(name);
    return Skin;
}