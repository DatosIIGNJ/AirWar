//
// Created by nano on 21/03/17.
//

#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


using namespace std;

ALLEGRO_DISPLAY *HomeS            = NULL;
ALLEGRO_DISPLAY *AboutS           = NULL;
ALLEGRO_DISPLAY *HighS            = NULL;
ALLEGRO_DISPLAY *janela           = NULL;

ALLEGRO_EVENT_QUEUE *evento       = NULL;
ALLEGRO_BITMAP *Home              = NULL;
ALLEGRO_BITMAP *Home2             = NULL;
ALLEGRO_BITMAP *Home3             = NULL;
ALLEGRO_BITMAP *Home4             = NULL;

ALLEGRO_BITMAP *About             = NULL;
ALLEGRO_BITMAP *About2            = NULL;
ALLEGRO_BITMAP *High              = NULL;
ALLEGRO_BITMAP *High2             = NULL;
ALLEGRO_BITMAP *Play              = NULL;

ALLEGRO_FONT *fonte               = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

ALLEGRO_MOUSE_STATE mousepos;


void AboutV();
void HomeV();
void HighV();
int PlayV();

void guardar(const char*[]);
void ordenar(char*,int);
const char * getdata();

const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;




char str[4567];

void manipular_entrada(ALLEGRO_EVENT evento);
void exibir_texto_centralizado();


int main() {


    //char Nombre[50]="rata";
    //int puntaje=2800;

    //ordenar(Nombre,puntaje);
    HomeV();
    cout<<str<<endl;

    return 0;
}


void manipular_entrada(ALLEGRO_EVENT evento) {
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (strlen(str) <= 25) {
            char temp[] = {evento.keyboard.unichar, '\0'};
            if (evento.keyboard.unichar == ' ') {
                strcat(str, temp);
            } else if (evento.keyboard.unichar >= '0' &&
                     evento.keyboard.unichar <= '9') {
                strcat(str, temp);
            } else if (evento.keyboard.unichar >= 'A' &&
                     evento.keyboard.unichar <= 'Z') {
                strcat(str, temp);
            } else if (evento.keyboard.unichar >= 'a' &&
                     evento.keyboard.unichar <= 'z') {
                strcat(str, temp);
            }
        }

        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(str) != 0) {
            str[strlen(str) - 1] = '\0';
        }
    }
}
void exibir_texto_centralizado() {
    if (strlen(str) > 0) {
        al_draw_text(fonte, al_map_rgb(0, 0, 0), LARGURA_TELA / 2,
                     (ALTURA_TELA - al_get_font_ascent(fonte)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }
}

void HomeV(){
    al_init();
    al_init_image_addon();
    al_install_mouse();

    int repaint=1;
    bool Salir =true;

    HomeS = al_create_display(650, 480);
    al_set_window_position(HomeS,350,150);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(HomeS));
    al_register_event_source(evento,al_get_mouse_event_source());

    Home = al_load_bitmap("/home/nano/Documentos/AirWar++/images/Home/Home.png");
    Home2 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/Home/Home2.png");
    Home3 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/Home/Home3.png");
    Home4 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/Home/Home4.png");


    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_display(HomeS);
            al_destroy_bitmap(Home);
            al_destroy_bitmap(Home2);
            al_destroy_bitmap(Home3);
            al_destroy_bitmap(Home4);
            break;
        }
        if (mousepos.x>264 && mousepos.x<415 && mousepos.y >224 && mousepos.y <277){
            al_draw_bitmap(Home2, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
                al_destroy_display(HomeS);
                al_destroy_bitmap(Home);
                al_destroy_bitmap(Home2);
                al_destroy_bitmap(Home3);
                al_destroy_bitmap(Home4);
                PlayV();
                break;
            }

        }else if (mousepos.x>252 && mousepos.x<428 && mousepos.y >298 && mousepos.y <353){
            al_draw_bitmap(Home3, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN ){
                al_destroy_display(HomeS);
                al_destroy_bitmap(Home);
                al_destroy_bitmap(Home2);
                al_destroy_bitmap(Home3);
                al_destroy_bitmap(Home4);
                AboutV();
                break;
            }

        }else if (mousepos.x>154 && mousepos.x<522 && mousepos.y >366 && mousepos.y <421) {
            al_draw_bitmap(Home4, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_destroy_display(HomeS);
                al_destroy_bitmap(Home);
                al_destroy_bitmap(Home2);
                al_destroy_bitmap(Home3);
                al_destroy_bitmap(Home4);
                HighV();
                break;
            }
        }else if (repaint) {
            al_draw_bitmap(Home, 0, 0, 0);
            al_flip_display();
        }

    }
}
void AboutV(){
    al_init();
    al_init_image_addon();
    al_install_mouse();

    int repaint=1;
    bool Salir =true;

    AboutS = al_create_display(650, 480);
    al_set_window_position(AboutS,350,150);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(AboutS));
    al_register_event_source(evento,al_get_mouse_event_source());

    About = al_load_bitmap("/home/nano/Documentos/AirWar++/images/About/About.png");
    About2 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/About/About2.png");

    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_bitmap(About);
            al_destroy_bitmap(About2);
            break;
        }

        if (mousepos.x>12 && mousepos.x<94 && mousepos.y >422 && mousepos.y <462) {
            al_draw_bitmap(About2, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_destroy_display(AboutS);
                al_destroy_bitmap(About);
                al_destroy_bitmap(About2);
                HomeV();
                break;
            }
        }else if (repaint) {
            al_draw_bitmap(About, 0, 0, 0);
            al_flip_display();
        }
    }

}
void HighV(){
    al_init();
    al_init_image_addon();
    al_install_mouse();

    int repaint=1;
    bool Salir =true;

    HighS = al_create_display(650, 480);
    al_set_window_position(HighS,350,150);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(HighS));
    al_register_event_source(evento,al_get_mouse_event_source());

    High = al_load_bitmap("/home/nano/Documentos/AirWar++/images/High Scores/High.png");
    High2 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/High Scores/High2.png");


    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_bitmap(High);
            al_destroy_bitmap(High2);
            break;
        }

        if (mousepos.x>12 && mousepos.x<94 && mousepos.y >422 && mousepos.y <462) {
            al_draw_bitmap(High2, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_destroy_display(HighS);
                al_destroy_bitmap(High);
                al_destroy_bitmap(High2);
                HomeV();
                break;
            }
        }else if (repaint) {
            al_draw_bitmap(High, 0, 0, 0);
            al_flip_display();
        }
    }

}

int PlayV(){
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela,350,150);
    al_set_window_title(janela, "Entrada de Texto");

    fila_eventos = al_create_event_queue();

    bool sair = false;
    bool concluido = false;

    strcpy(str, "");

    Play = al_load_bitmap("High.png");
    High2 = al_load_bitmap("/home/nano/Documentos/AirWar++/images/High Scores/High2.png");
    fonte = al_load_font("Alice.ttf", 42, 0);

    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());


    while (!sair) {
        while (!al_is_event_queue_empty(fila_eventos)) {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            al_get_mouse_state(&mousepos);

            if (!concluido) {
                manipular_entrada(evento);

                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    concluido = true;
                }

            }

            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                sair = true;
            }

        }

        al_draw_bitmap(Play, 0, 0, 0);

        if (!concluido) {
            al_draw_text(fonte, al_map_rgb(0,0,0), LARGURA_TELA / 2,
                         (ALTURA_TELA / 2 - al_get_font_ascent(fonte)) / 2,
                         ALLEGRO_ALIGN_CENTRE, "NICKNAME:");
        }

        exibir_texto_centralizado();
        al_flip_display();
    }

    al_destroy_bitmap(Play);
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}


void guardar(const char *Data[]){
    ofstream Guardar;
    Guardar.open("Datos.txt",ios::trunc);

    for(int i=0;i<10;i+=2){
        Guardar<<Data[i]<<" "<<Data[i+1]<<endl;
    }


}
void ordenar(char* nombre,int puntaje){
    FILE *miarchivo;
    char * archivo="Datos.txt";
    const char *Data[10];
    char nprimero[80],sprim[80],nsegundo[80],sseg[80],ntercero[80],sterc[80],ncuarto[80],scuar[80],nquinto[80],squi[80];

    miarchivo=fopen(archivo,"r");
    fscanf(miarchivo,"%s",&nprimero);
    fscanf(miarchivo,"%s",&sprim);
    int num=atoi(sprim);

    fscanf(miarchivo,"%s",&nsegundo);
    fscanf(miarchivo,"%s",&sseg);
    int num2=atoi(sseg);

    fscanf(miarchivo,"%s",&ntercero);
    fscanf(miarchivo,"%s",&sterc);
    int num3=atoi(sterc);

    fscanf(miarchivo,"%s",&ncuarto);
    fscanf(miarchivo,"%s",&scuar);
    int num4=atoi(scuar);

    fscanf(miarchivo,"%s",&nquinto);
    fscanf(miarchivo,"%s",&squi);
    int num5=atoi(squi);


    if (puntaje>num5 && puntaje<num4){
        string str=to_string(puntaje);

        Data[0]=nprimero;
        Data[1]=sprim;
        Data[2]=nsegundo;
        Data[3]=sseg;
        Data[4]=ntercero;
        Data[5]=sterc;
        Data[6]=ncuarto;
        Data[7]=scuar;
        Data[8]=nombre;
        Data[9]=str.c_str();
        guardar(Data);

    }else if (puntaje>num4 && puntaje<num3){
        string str=to_string(puntaje);
        Data[0]=nprimero;
        Data[1]=sprim;
        Data[2]=nsegundo;
        Data[3]=sseg;
        Data[4]=ntercero;
        Data[5]=sterc;
        Data[6]=nombre;
        Data[7]=str.c_str();
        Data[8]=ncuarto;
        Data[9]=scuar;
        guardar(Data);

    }else if (puntaje>num3 && puntaje<num2){
        string str=to_string(puntaje);
        Data[0]=nprimero;
        Data[1]=sprim;
        Data[2]=nsegundo;
        Data[3]=sseg;
        Data[4]=nombre;
        Data[5]=str.c_str();
        Data[6]=ntercero;
        Data[7]=sterc;
        Data[8]=ncuarto;
        Data[9]=scuar;
        guardar(Data);

    }else if (puntaje>num2 && puntaje<num){
        string str=to_string(puntaje);
        Data[0]=nprimero;
        Data[1]=sprim;
        Data[2]=nombre;
        Data[3]=str.c_str();
        Data[4]=nsegundo;
        Data[5]=sseg;
        Data[6]=ntercero;
        Data[7]=sterc;
        Data[8]=ncuarto;
        Data[9]=scuar;
        guardar(Data);

    }else if (puntaje>num){
        string str=to_string(puntaje);
        Data[0]=nombre;
        Data[1]=str.c_str();
        Data[2]=nprimero;
        Data[3]=sprim;
        Data[4]=nsegundo;
        Data[5]=sseg;
        Data[6]=ntercero;
        Data[7]=sterc;
        Data[8]=ncuarto;
        Data[9]=scuar;
        guardar(Data);

    }else{
        Data[0]=nprimero;
        Data[1]=sprim;
        Data[2]=nsegundo;
        Data[3]=sseg;
        Data[4]=ntercero;
        Data[5]=sterc;
        Data[6]=ncuarto;
        Data[7]=scuar;
        Data[8]=nquinto;
        Data[9]=squi;
        guardar(Data);
    }


}
const char * getdata(){
    FILE *miarchivo;
    char * archivo="Datos.txt";
    const char *Data[10];

    miarchivo=fopen(archivo,"r");
    fscanf(miarchivo,"%s",&Data[0]);
    fscanf(miarchivo,"%s",&Data[1]);

    fscanf(miarchivo,"%s",&Data[2]);
    fscanf(miarchivo,"%s",&Data[3]);

    fscanf(miarchivo,"%s",&Data[4]);
    fscanf(miarchivo,"%s",&Data[5]);

    fscanf(miarchivo,"%s",&Data[6]);
    fscanf(miarchivo,"%s",&Data[7]);

    fscanf(miarchivo,"%s",&Data[8]);
    fscanf(miarchivo,"%s",&Data[9]);

    return *Data;
}