//
// Created by gerardo on 29/03/17.
//

#ifndef AIRWAR_BALA_H
#define AIRWAR_BALA_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Bala{
private:
    int BalaX;
    int BalaY;
    int Pot;

public:
    Bala(int _X,int _Y,int _Pot);
    int getBalaX(){return BalaX;}
    void setBalaX(int BalaX) { Bala::BalaX = BalaX;}
    int getBalaY(){return BalaY;}
    void setBalaY(int BalaY) { Bala::BalaY = BalaY;}
    int getPot(){return Pot;}
    void setPot(int Pot) { Bala::Pot = Pot;}
    ALLEGRO_BITMAP *Dibujar(char *name);
    void DisparaNave();
    void DisparaEnemy();

};
#endif //AIRWAR_BALA_H
