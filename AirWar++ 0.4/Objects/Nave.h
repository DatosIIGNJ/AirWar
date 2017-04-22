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
    int BordeX =73;
    int BordeY=63;
    int orientation=2;
    int Salud=100;
    int Ndiparos = 0;
    int Puntaje = 0;
    int Vidas = 10;
    int Velocidad = 5;
    int PowerUps=0; //esto es nuevo

public:
    Nave(int _X,int _Y);
    int getVidas(){ return Vidas;}
    int getVelocidad(){ return Velocidad;}
    int getX(){ return X;}
    int getOR(){return orientation;}
    int getBordeX(){ return BordeX;}
    int getY(){ return Y;}
    int getBordeY(){ return BordeY;}
    int getSalud(){ return Salud;}
    void setSalud(int sal){Nave::Salud = sal;}
    void setOR(int OR){Nave::orientation = OR;}
    void setY(int Y){Nave::Y = Y;}
    void setX(int X){Nave::X = X;}
    void setVidas(int Vida){ Nave::Vidas = Vida;}
    void setVelocidad(int Vel){ Nave::Velocidad = Vel;}
    int getPowerUps(){ return PowerUps;} //esto es nuevo
    void setPowerUps(int Power){ Nave::PowerUps = Power;} //esto es nuevo
    ALLEGRO_BITMAP *Dibujar(char name[]);

};
#endif //AIRWAR_NAVE_H
