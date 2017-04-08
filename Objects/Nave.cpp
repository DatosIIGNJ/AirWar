//
// Created by gerardo on 28/03/17.
//

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Bala.h"

#include "Nave.h"



Nave::Nave(int _X,int _Y){
    X = _X;
    Y = _Y;
}

ALLEGRO_BITMAP* Nave::Dibujar(char *name){
    ALLEGRO_BITMAP *Skin;
    Skin = al_load_bitmap(name);
    return Skin;
}



