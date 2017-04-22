//
// Created by gerardo on 09/04/17.
//

#ifndef AIRWAR_OBJECTS_H
#define AIRWAR_OBJECTS_H

struct Proyectil{
    int x;
    int y;
    int dir;
    int destX;
    int destY;
    int potencia;
    int bordeX;
    int bordeY;
    int velocidad;
    bool activo;
};

struct Enemigo{
    int type;
    int x;
    int y;
    int potencia;
    int velocidad;
    int salud;
    int bordeX;
    int bordeY;
    bool activo;
    bool shot;
};

struct PowerUpBala{
    int x;
    int y;
    int dir;
    int destX;
    int destY;
    int potencia;
    int bordeX;
    int bordeY;
    int velocidad;
    bool activo;
    bool paraUsar;
};

struct PowerUpEscudo{
    int x;
    int y;
    int dir;
    int destX;
    int destY;
    int potencia;
    int bordeX;
    int bordeY;
    int velocidad;
    bool activo;
    bool paraUsar;
};
#endif //AIRWAR_OBJECTS_H
