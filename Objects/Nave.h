//
// Created by gerardo on 28/03/17.
//

#ifndef AIRWAR_NAVE_H
#define AIRWAR_NAVE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Nave{
private:
    int X;
    int Y;
    int Puntaje = 0;
    int Level;
    int Vidas = 3;
    int Velocidad = 4;

public:
    Nave(int _X,int _Y);
    int getVidas(){ return Vidas;}
    int getVelocidad(){ return Velocidad;}
    int getX(){ return X;}
    int getY(){ return Y;}
    void setY(int Y){Nave::Y = Y;}
    void setX(int X){Nave::X = X;}
    void setVidas(int Vida){ Nave::Vidas = Vida;}
    void setVelocidad(int Vel){ Nave::Velocidad = Vel;}
    ALLEGRO_BITMAP *Dibujar(char *name);
    ALLEGRO_BITMAP *Destruir();

};
#endif //AIRWAR_NAVE_H
