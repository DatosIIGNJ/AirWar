//
// Created by gerardo on 21/03/17.
//

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <pthread.h>
#include "Objects/Nave.h"
#include "Objects/Bala.h"

using namespace std;

char *NaveName = "/home/gerardo/CLionProjects/AirWar++/images/Nave.png";
char *BalaName = "/home/gerardo/CLionProjects/AirWar++/images/Bala.png";
int Y =-1400;

enum GAME_KEYS
{
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_P,
    KEY_SPACE
};

int key[] = { 0, 0, 0, 0, 0, 0};

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *evento;
ALLEGRO_TIMER *timer;
ALLEGRO_BITMAP *Fondo;


int main(){
    int repaint = 1;
    int repaintbala = 0;

    al_init();
    al_init_image_addon();
    al_install_keyboard();


    //Objetos

    Nave Player =  Nave(50,380);
    Nave Player2 =  Nave(50,0);
    for(int i= )
    Bala BalaNave(Player.getX()+45,Player.getY()+15,2);


    Fondo = al_load_bitmap("/home/gerardo/CLionProjects/AirWar++/images/Textura.jpg");

    display = al_create_display(650,480);
    evento = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(evento, al_get_display_event_source(display));
    al_register_event_source(evento, al_get_timer_event_source(timer));
    al_register_event_source(evento, al_get_keyboard_event_source());

    al_start_timer(timer);

    while (1)
    {

        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE){
                repaintbala = 1;
                BalaNave.setBalaX(Player.getX()+45);
                BalaNave.setBalaY(Player.getY()+15);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_P)
                key[KEY_P] = 1;

        }
        if (event.type == ALLEGRO_EVENT_KEY_UP)
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_P)
                key[KEY_P] = 0;

        }
        if (event.type == ALLEGRO_EVENT_TIMER){
            if (key[KEY_LEFT] && Player.getX()>=0)
                Player.setX(Player.getX()-4);
            if (key[KEY_RIGHT] && Player.getX()<=550)
                Player.setX(Player.getX()+4);;
            if (key[KEY_UP] && Player.getY()>=0)
                Player.setY(Player.getY()-4);
            if (key[KEY_DOWN]&& Player.getY()<=400)
                Player.setY(Player.getY()+4);
            if (repaintbala){
                if (BalaNave.getBalaY()>-30){
                    BalaNave.DisparaNave();
                }
                else
                    repaintbala = 0;
            }
            repaint = 1;
        }

        if (repaint){
            if (repaint){
                al_draw_bitmap(Fondo,0,Y,0);
                Y+=4;
                if (Y == 0)
                     Y = -1400;
            }

            if (repaintbala)
                al_draw_bitmap(BalaNave.Dibujar(BalaName),BalaNave.getBalaX(),BalaNave.getBalaY(),0);

            al_draw_bitmap(Player.Dibujar(NaveName),Player.getX(),Player.getY(),0);
            al_draw_bitmap(Player2.Dibujar(NaveName),Player2.getX(),Player2.getY(),ALLEGRO_FLIP_VERTICAL);
            if (key[KEY_P]){
                NaveName = "/home/gerardo/CLionProjects/AirWar++/images/Boom.png";
            }

            al_flip_display();
            repaint = 0;
        }

    }
    al_destroy_bitmap(Fondo);
    al_destroy_event_queue(evento);
    al_destroy_timer(timer);
    return 0;

}