//
// Created by gerardo on 21/03/17.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Objects/Nave.h"
#include "Objects/Objects.h"
#define BUFSIZE 1000
#define PORT 8088
using namespace std;

//_____________________________________

//-------Variables Globales-----------
const int NumBalas=10;
const int NumEnemigos=7;
int Y =-2586;
int Kills=0;
int Puntaje=0;
char PlayerName[40]="JDesq";
int PowerUpsBalaConseguidos=0;
int PowerUpsEscudoConseguidos=0;
int n;
ALLEGRO_DISPLAY *display         = NULL;
ALLEGRO_EVENT_QUEUE *evento      = NULL;
ALLEGRO_TIMER *timer             = NULL;
ALLEGRO_BITMAP *Fondo            = NULL;
ALLEGRO_BITMAP *BalaIMG          = NULL;
ALLEGRO_BITMAP *Enemy1           = NULL;
ALLEGRO_BITMAP *PSprite          = NULL;
ALLEGRO_FONT *Vidas              = NULL;
ALLEGRO_THREAD *HiloServer       = NULL;
ALLEGRO_SAMPLE *Disparo          = NULL;
ALLEGRO_SAMPLE *ExplotaE         = NULL;
ALLEGRO_SAMPLE *DeadNave         = NULL;
ALLEGRO_BITMAP *PowerUpBalaIMG   = NULL; //NUevo
ALLEGRO_BITMAP *PowerUpEscudoIMG   = NULL; //NUevo
ALLEGRO_DISPLAY *HomeS            = NULL;
ALLEGRO_DISPLAY *AboutS           = NULL;
ALLEGRO_DISPLAY *HighS            = NULL;
ALLEGRO_DISPLAY *janela           = NULL;
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
ALLEGRO_MOUSE_STATE mousepos;

enum GAME_KEYS
{
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_ESC,
    KEY_SPACE
};
int key[] = { 0, 0, 0, 0, 0, 0};


void AboutV();
void HomeV();
void HighV();
void PlayV();
void JuegoV();

void guardar(const char*[]);
void ordenar(char*,int);
void getdata();

const int LARGURA_TELA = 640;
const int ALTURA_TELA = 480;
char str[4567];
void manipular_entrada(ALLEGRO_EVENT evento);
void exibir_texto_centralizado();

void InitBalas(Proyectil Bala[], int Tamanho);
void Tirabalas(Proyectil Bala[], int Tamanho, Nave Player);
void ActualizaBalas(Proyectil Bala[], int Tamanho);
void DibujaBalas(Proyectil Bala[],PowerUpBala PowerBala[], int Tamanho);
void BalaChoca(Proyectil Bala[], int B_Tamanho, Enemigo Enemy[],PowerUpBala PowerBala[],PowerUpEscudo PowerEscudo[], int E_Tamanho,Nave Player);

void InitBalasE(Proyectil BalaE[], int Tamanho);
void TirabalasE(Proyectil BalaE[], int Tamanho, Enemigo Enemy[],Nave Player);
void ActualizaBalasE(Proyectil BalaE[], int Tamanho,Enemigo Enemy[],Nave Player);
void DibujaBalasE(Proyectil BalaE[], int Tamanho);
int BalaChocaE(Proyectil BalaE[],PowerUpEscudo PowerEscudo[], int B_Tamanho,Nave Player);

void InitEnemigos(Enemigo Enemy[], int tamanho);
void LiberaEnemigos(Enemigo Enemy[], int tamanho);
void ActualizaEnemigos(Enemigo Enemy[], int tamanho);
void DibujaEnemigos(Enemigo Enemy[], int tamanho);
int EnemigoChoca(Enemigo Enemy[],PowerUpEscudo PowerEscudo[], int tamanho, Nave Player);

void InitPowerUpBala(PowerUpBala PowerBala[], int Tamanho); //nuevo
void LiberaPowerUpBala(PowerUpBala PowerBala[], int tamanho);
void ActualizaPowerUpBala(PowerUpBala PowerBala[], int tamanho);
void DibujaPowerUpBala(PowerUpBala PowerBala[], int tamanho);
int PowerUpBalaChoca(PowerUpBala PowerBala[],Proyectil Bala[], int tamanho, Nave Player);

void InitPowerUpEscudo(PowerUpEscudo PowerEscudo[], int Tamanho); //nuevo
void LiberaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho);
void ActualizaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho);
void DibujaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho);
int PowerUpEscudoChoca(PowerUpEscudo PowerEscudo[],Proyectil Bala[], int tamanho, Nave Player);

int Colision(int b1_x, int b1_y, int b1_w, int b1_h, int b2_x, int b2_y, int b2_w, int b2_h) {
    if ((b1_x > b2_x + b2_w - 1) || // is b1 on the right side of b2?
        (b1_y > b2_y + b2_h - 1) || // is b1 under b2?
        (b2_x > b1_x + b1_w - 1) || // is b2 on the right side of b1?
        (b2_y > b1_y + b1_h - 1))   // is b2 under b1?
    {
        // no collision
        return 0;
    }

    // collision
    return 1;
}

void *Escucha(ALLEGRO_THREAD *thr, void *args){
    char buffer[BUFSIZE];

    // define our address structure, stores our port
    // and our ip address, and the socket type, etc..
    struct sockaddr_in addrinfo;
    addrinfo.sin_family = AF_INET;
    addrinfo.sin_port = htons(PORT);
    addrinfo.sin_addr.s_addr = INADDR_ANY;

    // creacion del socket.
    int sock;
    if ((sock = socket(addrinfo.sin_family, SOCK_STREAM, 0)) < 0) {
        cout << "Error in creating the socket.";
    }

    // iniciar el socket server
    if (bind(sock, (struct sockaddr *) &addrinfo, sizeof(addrinfo)) != 0) {
        cout << "Adress Bussy.";
    }

    // tener el server socket en escucha de conexiones
    if (listen(sock, 5) != 0) {
        cout << "Error in opening listener.";
    }

    char *msg = (char *) "success! You are connected.\r\n";
    while(1){
        cout << "Waiting for connections...." << endl;

        struct sockaddr_in client_addr;

        socklen_t sin_size = sizeof(client_addr);

        if (int cliente =
                accept(sock, (struct sockaddr *) &client_addr, &sin_size)) {
            cout << "recieved new connection from " << inet_ntoa(client_addr.sin_addr) << endl;

            while (1) {
                n = read(cliente,buffer,255 );
                int num = recv(cliente, buffer, BUFSIZE, 0);
                if (num < 1) break;

                buffer[num] = '\0';
                if (buffer[num - 1] == '\n')
                    buffer[num - 1] = '\0';
                cout << buffer << endl;
                strcpy(buffer, "");
                if (n < 0)
                {
                    perror("ERROR writing to socket");
                }else if(n==6){
                    cout<<"Dispara"<<endl;
                }else if(n==5){
                    cout<<"Arriba"<<endl;
                }else if(n==7){
                    cout<<"Abajo"<<endl;
                }else if(n==9){
                    cout<<"Derecha"<<endl;
                }else if(n==11){
                    cout<<"Izquierda"<<endl;
                }
            }
        } else {
            cout << "Error in accepting new connection." << endl;
        }
    }
}

int main(){

    HomeV();

    return 0;

}


//__________________________________________________
//-------------Ventanas-----------------------------
//__________________________________________________

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
void getdata(){
    FILE *miarchivo;
    char * archivo="Datos.txt";
    char nprimero[80],sprim[80],nsegundo[80],sseg[80],ntercero[80],sterc[80],ncuarto[80],scuar[80],nquinto[80],squi[80];

    miarchivo=fopen(archivo,"r");
    fscanf(miarchivo,"%s",&nprimero);
    fscanf(miarchivo,"%s",&sprim);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),150, 100,ALLEGRO_ALIGN_CENTRE,nprimero);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),450, 100,ALLEGRO_ALIGN_CENTRE,sprim);

    fscanf(miarchivo,"%s",&nsegundo);
    fscanf(miarchivo,"%s",&sseg);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),150, 150,ALLEGRO_ALIGN_CENTRE,nsegundo);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),450, 150,ALLEGRO_ALIGN_CENTRE,sseg);

    fscanf(miarchivo,"%s",&ntercero);
    fscanf(miarchivo,"%s",&sterc);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),150, 200,ALLEGRO_ALIGN_CENTRE,ntercero);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),450, 200,ALLEGRO_ALIGN_CENTRE,sterc);

    fscanf(miarchivo,"%s",&ncuarto);
    fscanf(miarchivo,"%s",&scuar);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),150, 250,ALLEGRO_ALIGN_CENTRE,ncuarto);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),450, 250,ALLEGRO_ALIGN_CENTRE,scuar);

    fscanf(miarchivo,"%s",&nquinto);
    fscanf(miarchivo,"%s",&squi);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),150, 300,ALLEGRO_ALIGN_CENTRE,nquinto);
    al_draw_text(fonte,al_map_rgb(0, 0, 0),450, 300,ALLEGRO_ALIGN_CENTRE,squi);

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

    Home = al_load_bitmap("images/Home/Home.png");
    Home2 = al_load_bitmap("images/Home/Home2.png");
    Home3 = al_load_bitmap("images/Home/Home3.png");
    Home4 = al_load_bitmap("images/Home/Home4.png");


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

    About = al_load_bitmap("images/About/About.png");
    About2 = al_load_bitmap("images/About/About2.png");

    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_bitmap(About);
            al_destroy_bitmap(About2);
            Salir=false;
        }

        if (mousepos.x>12 && mousepos.x<94 && mousepos.y >422 && mousepos.y <462) {
            al_draw_bitmap(About2, 0, 0, 0);
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_destroy_display(AboutS);
                al_destroy_bitmap(About);
                al_destroy_bitmap(About2);
                HomeV();
                Salir=false;
            }
        }else if (repaint) {
            al_draw_bitmap(About, 0, 0, 0);
            al_flip_display();
        }
    }

}
void HighV(){
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_mouse();

    int repaint=1;
    bool Salir =true;

    HighS = al_create_display(650, 480);
    al_set_window_position(HighS,350,150);
    evento = al_create_event_queue();

    al_register_event_source(evento, al_get_display_event_source(HighS));
    al_register_event_source(evento,al_get_mouse_event_source());

    fonte = al_load_font("Fonts/Alice.ttf", 42, 0);
    High = al_load_bitmap("images/High Scores/High.png");
    High2 = al_load_bitmap("images/High Scores/High2.png");


    while (Salir){
        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);
        al_get_mouse_state(&mousepos);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            al_destroy_bitmap(High);
            al_destroy_bitmap(High2);
            Salir=false;
        }

        if (mousepos.x>12 && mousepos.x<94 && mousepos.y >422 && mousepos.y <462) {
            al_draw_bitmap(High2, 0, 0, 0);
            al_draw_filled_rectangle(100,90,520,350,al_map_rgb(255,255,255));
            getdata();
            al_flip_display();
            if (event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                al_destroy_display(HighS);
                al_destroy_bitmap(High);
                al_destroy_bitmap(High2);
                HomeV();
                Salir=false;
            }
        }else if (repaint) {
            al_draw_bitmap(High, 0, 0, 0);
            al_draw_filled_rectangle(100,90,520,350,al_map_rgb(255,255,255));
            getdata();
            al_flip_display();
        }
    }

}
void PlayV(){
    al_init();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    al_set_window_position(janela,350,150);
    al_set_window_title(janela, "Entrada de Texto");

    evento = al_create_event_queue();

    int repaint=1;

    bool sair = false;
    bool concluido = false;

    strcpy(str, "");

    Play = al_load_bitmap("images/Play/High.jpeg");
    High2 = al_load_bitmap("images/High Scores/High2.png");
    fonte = al_load_font("Fonts/Alice.ttf", 42, 0);

    al_register_event_source(evento, al_get_display_event_source(janela));
    al_register_event_source(evento, al_get_keyboard_event_source());


    while (!sair) {
        while(!al_is_event_queue_empty(evento)) {
            ALLEGRO_EVENT event;
            al_wait_for_event(evento, &event);
            al_get_mouse_state(&mousepos);
            if (!concluido) {
                manipular_entrada(event);

                if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    concluido = true;
                }
            }

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                sair = true;
            }
            if (mousepos.x>12 && mousepos.x<94 && mousepos.y >422 && mousepos.y <462) {
                al_draw_bitmap(High2, 0, 0, 0);
                al_flip_display();
                if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    al_destroy_display(AboutS);
                    al_destroy_bitmap(About);
                    al_destroy_bitmap(About2);
                    HomeV();
                    sair = true;
                }
            }
        }
        if (concluido){
            al_destroy_bitmap(Play);
            al_destroy_bitmap(High2);
            JuegoV();
            sair=true;

        }
        if (repaint) {
            al_draw_bitmap(Play, 0, 0, 0);
            exibir_texto_centralizado();
            al_flip_display();
        }
    }

    al_destroy_bitmap(Play);
    al_destroy_font(fonte);
    al_destroy_event_queue(evento);
}
void JuegoV(){
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(5);
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();

    al_destroy_display(janela);
    bool Salir =true;
    int repaint = 1;

    //------------Objetos-----------------
    Nave Player = Nave(300,380);
    Proyectil BalaNAVE[NumBalas];
    PowerUpBala PowerBala [NumEnemigos]; //nuevo
    PowerUpEscudo PowerEscudo [NumEnemigos]; //nuevo
    Proyectil BalaEnemigo[10];
    Enemigo Enemy[NumEnemigos];

    //------------Carga de archivos-----------------
    Fondo = al_load_bitmap("images/Texture.png");
    BalaIMG = al_load_bitmap("images/Bala.png");
    PowerUpBalaIMG = al_load_bitmap("images/power1.png");//nuevo
    PowerUpEscudoIMG = al_load_bitmap("images/power2.png");//nuevo
    Disparo = al_load_sample("Sounds/Shot.wav");
    ExplotaE = al_load_sample("Sounds/ExplodeE.WAV");
    Vidas = al_load_font("Fonts/arial.ttf",12,0);
    DeadNave = al_load_sample("Sounds/DeadN.wav");
    PSprite = Player.Dibujar("images/Nave2.png");

    display = al_create_display(650,480);
    al_set_window_position(display,350,150);
    evento = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);
    al_register_event_source(evento, al_get_mouse_event_source());
    al_register_event_source(evento, al_get_display_event_source(display));
    al_register_event_source(evento, al_get_timer_event_source(timer));
    al_register_event_source(evento, al_get_keyboard_event_source());

    //Threads
    srand(time(NULL));
    HiloServer = al_create_thread(Escucha,NULL);
    al_start_thread(HiloServer);

    InitBalas(BalaNAVE,NumBalas);
    InitPowerUpBala(PowerBala,NumEnemigos);//nuevo
    InitPowerUpEscudo(PowerEscudo,NumEnemigos);//nuevo
    InitBalasE(BalaEnemigo,NumEnemigos);
    InitEnemigos(Enemy,NumEnemigos);

    al_start_timer(timer);
    while (!key[KEY_ESC] && Salir) {

        ALLEGRO_EVENT event;
        al_wait_for_event(evento, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            Salir = false;

        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 1;
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE || n == 6) {
                key[KEY_SPACE] = 1;
                Tirabalas(BalaNAVE, NumBalas, Player);
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                key[KEY_ESC] = 1;
        }

        if (event.type == ALLEGRO_EVENT_KEY_UP) {
            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                key[KEY_LEFT] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                key[KEY_RIGHT] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_UP)
                key[KEY_UP] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
                key[KEY_DOWN] = 0;
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                key[KEY_ESC] = 0;
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            if ((key[KEY_LEFT] && Player.getX() >= 0) || (n == 11 && Player.getX() >= 0)) {
                Player.setX(Player.getX() - Player.getVelocidad());
                Player.setOR(1);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo1.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave1.png");
                }
            }

            if ((key[KEY_RIGHT] && Player.getX() <= 575) || (n == 9 && Player.getX() <= 575)) {
                Player.setX(Player.getX() + Player.getVelocidad());
                Player.setOR(3);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo3.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave3.png");
                }
            }

            if ((key[KEY_UP] && Player.getY() >= 0) || (n == 5 && Player.getY() >= 0)) {
                Player.setY(Player.getY() - Player.getVelocidad());
                Player.setOR(2);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo2.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave2.png");
                }
            }

            if ((key[KEY_DOWN] && Player.getY() <= 415) || (n == 7 && Player.getY() <= 415)) {
                Player.setY(Player.getY() + Player.getVelocidad());
                Player.setOR(4);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo4.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave4.png");
                }
            }

            if(key[KEY_UP] && key[KEY_LEFT]) {
                Player.setOR(5);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo5.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave5.png");
                }
            }

            if(key[KEY_UP] && key[KEY_RIGHT]) {
                Player.setOR(6);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo6.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave6.png");
                }
            }

            if(key[KEY_DOWN] && key[KEY_RIGHT]){
                Player.setOR(8);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo8.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave8.png");
                }
            }

            if(key[KEY_DOWN] && key[KEY_LEFT]) {
                Player.setOR(7);
                if(PowerEscudo->paraUsar==true){
                    PSprite = Player.Dibujar("images/NaveEscudo7.png");
                }else{
                    PSprite = Player.Dibujar("images/Nave7.png");
                }
            }

            if (key[KEY_SPACE]) {
                ActualizaBalas(BalaNAVE, NumBalas);
            }

            TirabalasE(BalaEnemigo,NumEnemigos,Enemy,Player);
            ActualizaBalasE(BalaEnemigo,NumEnemigos,Enemy,Player);
            Player.setSalud(BalaChocaE(BalaEnemigo,PowerEscudo,NumEnemigos,Player));
            PowerUpBalaChoca(PowerBala,BalaNAVE, NumEnemigos, Player);
            PowerUpEscudoChoca(PowerEscudo,BalaNAVE, NumEnemigos, Player);
            BalaChoca(BalaNAVE, NumBalas, Enemy,PowerBala,PowerEscudo, NumEnemigos,Player);
            Player.setVidas(EnemigoChoca(Enemy,PowerEscudo, NumEnemigos, Player));
            LiberaEnemigos(Enemy, NumEnemigos);
            ActualizaEnemigos(Enemy, NumEnemigos);
            LiberaPowerUpBala(PowerBala, NumEnemigos); //nuevo
            ActualizaPowerUpBala(PowerBala, NumEnemigos); //nuevo
            LiberaPowerUpEscudo(PowerEscudo, NumEnemigos); //nuevo
            ActualizaPowerUpEscudo(PowerEscudo, NumEnemigos); //nuevo

            if (Kills == 10) {
                Player.setVidas(Player.getVidas() + 1);
                cout << "Ganaste una Vida!"<<endl;
                Kills=0;
            }

            repaint = 1;
        }
        if (key[KEY_ESC])
            Salir = false;


        if(Player.getVidas() == 0){

            ordenar(str,Puntaje);
            cout << "-----------------------------------------" << endl;
            cout << endl << "Moriste"<< endl;
            cout << "Tu puntaje es: " << Puntaje << endl;
            break;
        }
        if(Player.getSalud() <= 0){
            Player.setVidas(Player.getVidas()-1);
            cout << "Te quedan: " << Player.getVidas() << " vidas" << endl;
            PSprite = Player.Dibujar("images/Boom.png");
            Player.setSalud(100);
            if (rand()%100==0){
                Player.setX(300);
                Player.setY(380);
                PSprite = Player.Dibujar("images/Nave2.png");
            }

        }


        if (repaint){
            al_clear_to_color(al_map_rgb(0,0,0));
            if (repaint){al_draw_bitmap(Fondo,0,Y,0); Y+=2; if (Y>=-544) Y=-2586;}
            al_draw_bitmap(PSprite,Player.getX(),Player.getY(),0);
            DibujaBalas(BalaNAVE,PowerBala,NumBalas);
            DibujaBalasE(BalaEnemigo,NumEnemigos);
            DibujaEnemigos(Enemy,NumEnemigos);
            DibujaPowerUpBala(PowerBala,NumEnemigos);//nuevo
            DibujaPowerUpEscudo(PowerEscudo,NumEnemigos);//nuevo
            al_draw_filled_rectangle(0,0,650,20,al_map_rgb(0,0,0));
            al_draw_textf(Vidas, al_map_rgb(255,255,255),30,4,ALLEGRO_ALIGN_CENTRE,"Vidas: %i", Player.getVidas());
            al_draw_textf(Vidas, al_map_rgb(255,255,255),120,4,ALLEGRO_ALIGN_CENTRE,"Salud: %i", Player.getSalud());
            al_draw_text(Vidas, al_map_rgb(255,255,255),300,4,ALLEGRO_ALIGN_CENTRE,str);
            al_draw_textf(Vidas, al_map_rgb(255,255,255),580,4,ALLEGRO_ALIGN_CENTRE,"Puntaje: %i", Puntaje);
            al_flip_display();
            repaint = 0;

        }

    }
    al_destroy_display(display);
    al_destroy_event_queue(evento);
    al_destroy_timer(timer);
    al_destroy_bitmap(Fondo);
    al_destroy_bitmap(BalaIMG);
    al_destroy_bitmap(Enemy1);
    al_destroy_bitmap(PSprite);
    al_destroy_bitmap(PowerUpBalaIMG);
    al_destroy_bitmap(PowerUpEscudoIMG);
    al_destroy_font(Vidas);
    al_destroy_sample(Disparo);
    al_destroy_sample(ExplotaE);
    al_destroy_sample(DeadNave);
}




//_________________________________________________
//---------Func. Balas-------------
void InitBalas(Proyectil Bala[], int Tamanho){
    for(int i=0;i< Tamanho;i++){
        Bala[i].velocidad=7;
        Bala[i].bordeX=5;
        Bala[i].bordeY=5;
        Bala[i].activo = false;
    }

}
void Tirabalas(Proyectil Bala[], int Tamanho, Nave Player){
    for(int i=0;i< Tamanho;i++) {
        if (!Bala[i].activo){
            al_play_sample(Disparo, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
            Bala[i].x = Player.getX()+36;
            Bala[i].y = Player.getY()+32;
            Bala[i].dir=Player.getOR();
            Bala[i].activo=true;
            break;
        }
    }
}
void ActualizaBalas(Proyectil Bala[], int Tamanho){
    for(int i=0;i< Tamanho;i++) {
        if (Bala[i].activo){
            if(Bala[i].dir==1) {
                Bala[i].x -= Bala[i].velocidad;
                if (Bala[i].x < -15)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==2) {
                Bala[i].y -= Bala[i].velocidad;
                if (Bala[i].y < -30)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==3) {
                Bala[i].x += Bala[i].velocidad;
                if (Bala[i].x > 680)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==4) {
                Bala[i].y += Bala[i].velocidad;
                if (Bala[i].y > 490)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==5) {
                Bala[i].x -= Bala[i].velocidad;
                Bala[i].y -= Bala[i].velocidad;
                if (Bala[i].y < -30 || Bala[i].x < -10)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==6) {
                Bala[i].x += Bala[i].velocidad;
                Bala[i].y -= Bala[i].velocidad;
                if (Bala[i].y < -30 || Bala[i].x > 680)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==7) {
                Bala[i].x -= Bala[i].velocidad;
                Bala[i].y += Bala[i].velocidad;
                if (Bala[i].y > 490 || Bala[i].x < -10)
                    Bala[i].activo = false;
            }
            else if(Bala[i].dir==8) {
                Bala[i].x += Bala[i].velocidad;
                Bala[i].y += Bala[i].velocidad;
                if (Bala[i].y >490 || Bala[i].x >680)
                    Bala[i].activo = false;
            }
        }
    }
}
void DibujaBalas(Proyectil Bala[],PowerUpBala PowerBala[], int Tamanho){
    for(int i=0;i< Tamanho;i++) {
        if (Bala[i].activo){
            if (PowerBala[i].paraUsar==true){
                al_draw_filled_circle(Bala[i].x,Bala[i].y,8,al_map_rgb(216,30,5));
            }else{
                al_draw_filled_circle(Bala[i].x,Bala[i].y,4,al_map_rgb(0,0,0));
            }
        }
    }
}
void BalaChoca(Proyectil Bala[], int B_Tamanho, Enemigo Enemy[],PowerUpBala PowerBala[],PowerUpEscudo PowerEscudo[], int E_Tamanho,Nave Player){
    for(int i=0;i<B_Tamanho;i++){
        for(int j=0;j<E_Tamanho;j++){
            if(Colision(Bala[i].x,Bala[i].y,Bala[i].bordeX,Bala[i].bordeY,Enemy[j].x,Enemy[j].y,Enemy[j].bordeX,Enemy[j].bordeY) && (Bala[i].activo && Enemy[j].activo)){
                al_play_sample(ExplotaE, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                Bala[i].activo=false;
                Enemy[j].activo= false;
                Puntaje += 100;
                Kills++;
                PowerBala->paraUsar=false;
            }else if(Colision(Bala[i].x,Bala[i].y,Bala[i].bordeX,Bala[i].bordeY,PowerBala[j].x,PowerBala[j].y,PowerBala[j].bordeX,PowerBala[j].bordeY) && (Bala[i].activo && PowerBala[j].activo)){
                Bala[i].activo=false; //esto es nuevo
                PowerUpsBalaConseguidos++;
                cout << "Has conseguido " << PowerUpsBalaConseguidos << " power ups bala" << endl; //esto es nuevo
                PowerBala[j].activo= false; //esto es nuevo
                PowerBala->paraUsar=true;
                if (PowerBala[i].paraUsar==true){ //esto es nuevo
                    al_draw_filled_circle(Bala[i].x,Bala[i].y,8,al_map_rgb(216,30,5));
                }else{
                    al_draw_filled_circle(Bala[i].x,Bala[i].y,4,al_map_rgb(0,0,0));
                }
            }else if(Colision(Bala[i].x,Bala[i].y,Bala[i].bordeX,Bala[i].bordeY,PowerEscudo[j].x,PowerEscudo[j].y,PowerEscudo[j].bordeX,PowerEscudo[j].bordeY) && (Bala[i].activo && PowerEscudo[j].activo)){
                Bala[i].activo=false; //esto es nuevo
                PowerUpsEscudoConseguidos++;
                cout << "Has conseguido " << PowerUpsEscudoConseguidos << " power ups escudo" << endl; //esto es nuevo
                PowerEscudo[j].activo= false; //esto es nuevo
                PowerEscudo->paraUsar=true;
            }
        }
    }
}

//---------Func. PowerUpBala-------------
void InitPowerUpBala(PowerUpBala PowerBala[], int tamanho){
    for(int i=0;i< tamanho;i++){
        PowerBala[i].velocidad=3;
        PowerBala[i].bordeX=50;
        PowerBala[i].bordeY=50;
        PowerBala[i].activo = false;
        PowerBala[i].paraUsar = false;
    }
}
void LiberaPowerUpBala(PowerUpBala PowerBala[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (!PowerBala[i].activo) {
            if ((rand() % 8000) == 0) {
                PowerBala[i].x = 60+ rand() % (650-120);
                PowerBala[i].y = 0;
                PowerBala[i].activo = true;
                break;
            }
        }
    }
}
void ActualizaPowerUpBala(PowerUpBala PowerBala[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (PowerBala[i].activo){
            PowerBala[i].y += PowerBala[i].velocidad;
            if (PowerBala[i].y > 450)
                PowerBala[i].activo= false;
        }
    }
}
void DibujaPowerUpBala(PowerUpBala PowerBala[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (PowerBala[i].activo){
            al_draw_bitmap(PowerUpBalaIMG, PowerBala[i].x, PowerBala[i].y, 0);
        }
    }
}
int PowerUpBalaChoca(PowerUpBala PowerBala[],Proyectil Bala[], int tamanho, Nave Player){
    for(int i=0; i< tamanho; i++) {
        if (PowerBala[i].activo) {
            if (Colision(PowerBala[i].x, PowerBala[i].y, PowerBala[i].bordeX, PowerBala[i].bordeY, Player.getX() + 10, Player.getY() + 10, Player.getBordeX(), Player.getBordeY())) {
                PowerUpsBalaConseguidos++; //esto es nuevo
                cout << "Has conseguido " << PowerUpsBalaConseguidos << " power ups bala" << endl;
                PowerBala[i].activo = false;
                PowerBala->paraUsar=true;
                if (PowerBala[i].paraUsar==true){ //esto es nuevo
                    al_draw_filled_circle(Bala[i].x,Bala[i].y,8,al_map_rgb(216,30,5));
                }else{
                    al_draw_filled_circle(Bala[i].x,Bala[i].y,4,al_map_rgb(0,0,0));
                }
            }
        }
    }
}

//---------Func. PowerUpEscudo-------------
void InitPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho){
    for(int i=0;i< tamanho;i++){
        PowerEscudo[i].velocidad=3;
        PowerEscudo[i].bordeX=50;
        PowerEscudo[i].bordeY=50;
        PowerEscudo[i].activo = false;
        PowerEscudo[i].paraUsar = false;
    }
}
void LiberaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (!PowerEscudo[i].activo) {
            if ((rand() % 8000) == 0) {
                PowerEscudo[i].x = 60+ rand() % (650-120);
                PowerEscudo[i].y = 0;
                PowerEscudo[i].activo = true;
                break;
            }
        }
    }
}
void ActualizaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (PowerEscudo[i].activo){
            PowerEscudo[i].y += PowerEscudo[i].velocidad;
            if (PowerEscudo[i].y > 450)
                PowerEscudo[i].activo= false;
        }
    }
}
void DibujaPowerUpEscudo(PowerUpEscudo PowerEscudo[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (PowerEscudo[i].activo){
            al_draw_bitmap(PowerUpEscudoIMG, PowerEscudo[i].x, PowerEscudo[i].y, 0);
        }
    }
}
int PowerUpEscudoChoca(PowerUpEscudo PowerEscudo[],Proyectil Bala[], int tamanho, Nave Player){
    for(int i=0; i< tamanho; i++) {
        if (PowerEscudo[i].activo) {
            if (Colision(PowerEscudo[i].x, PowerEscudo[i].y, PowerEscudo[i].bordeX, PowerEscudo[i].bordeY, Player.getX() + 10, Player.getY() + 10, Player.getBordeX(), Player.getBordeY())) {
                PowerUpsEscudoConseguidos++; //esto es nuevo
                cout << "Has conseguido " << PowerUpsEscudoConseguidos << " power ups escudo" << endl;
                PowerEscudo[i].activo = false;
                PowerEscudo->paraUsar=true;
            }
        }
    }
}

//--------Func. BalaE.........................................
void InitBalasE(Proyectil BalaE[], int Tamanho){
    for(int i=0;i< Tamanho;i++){
        BalaE[i].velocidad=6;
        BalaE[i].bordeX=5;
        BalaE[i].bordeY=5;
        BalaE[i].activo = false;
    }
}
void TirabalasE(Proyectil BalaE[], int Tamanho, Enemigo Enemy[],Nave Player){
    for(int i=0;i< Tamanho;i++) {
        if(Enemy[i].activo && Enemy[i].shot) {
            for (int j = 0; j < Tamanho; j++) {
                if (!BalaE[j].activo && (rand() % 1000 == 0)) {
                    BalaE[j].x = Enemy[i].x + 25;
                    BalaE[j].potencia = Enemy[i].potencia;
                    BalaE[j].destX = Player.getX();
                    BalaE[j].destY = Player.getY();
                    BalaE[j].y = Enemy[i].y + 30;
                    BalaE[j].activo = true;
                    break;
                }
            }
        }
    }
}
void ActualizaBalasE(Proyectil BalaE[], int Tamanho, Enemigo Enemy[],Nave Player){
    for(int i=0;i< Tamanho;i++) {
        for(int j=0; j < Tamanho;j++){
            if (BalaE[j].activo) {
                if (Enemy[i].type == 3 || Enemy[i].type==4){
                    if(BalaE[j].destX > BalaE[j].x && BalaE[j].destY > BalaE[j].y){
                        BalaE[j].x += BalaE[j].velocidad;
                        BalaE[j].y += BalaE[j].velocidad;
                        if (BalaE[j].x > 690 || BalaE[j].y > 500)
                            BalaE[i].activo = false;
                    }
                    else if(BalaE[j].destX < BalaE[j].x && BalaE[j].destY > BalaE[j].y){
                        BalaE[j].x -= BalaE[j].velocidad;
                        BalaE[j].y += BalaE[j].velocidad;
                        if (BalaE[j].x < -10 || BalaE[j].y > 500)
                            BalaE[i].activo = false;
                    }
                    else if(BalaE[j].destX < BalaE[j].x && BalaE[j].destY < BalaE[j].y){
                        BalaE[j].x -= BalaE[j].velocidad;
                        BalaE[j].y -= BalaE[j].velocidad;
                        if (BalaE[j].x < -10 || BalaE[j].y < -10)
                            BalaE[i].activo = false;
                    }
                    else if(BalaE[j].destX > BalaE[j].x && BalaE[j].destY < BalaE[j].y){
                        BalaE[j].x += BalaE[j].velocidad;
                        BalaE[j].y -= BalaE[j].velocidad;
                        if (BalaE[j].x > 690 || BalaE[j].y < -10)
                            BalaE[i].activo = false;
                    }

                }
                else {
                    BalaE[j].y += BalaE[j].velocidad;
                    if (BalaE[j].y > 500)
                        BalaE[j].activo = false;
                }

            }
        }
    }
}
void DibujaBalasE(Proyectil BalaE[], int Tamanho){
    for(int i=0;i< Tamanho;i++) {
        if (BalaE[i].activo){
            al_draw_filled_circle(BalaE[i].x,BalaE[i].y,4,al_map_rgb(0,0,0));
        }

    }
}
int BalaChocaE(Proyectil BalaE[],PowerUpEscudo PowerEscudo[], int B_Tamanho,Nave Player){
    for(int i=0; i < B_Tamanho;i++){
        if(Colision(BalaE[i].x,BalaE[i].y,BalaE[i].bordeX,BalaE[i].bordeY,Player.getX(),Player.getY(),Player.getBordeX(),Player.getBordeY()) && BalaE[i].activo){
            if(PowerEscudo->paraUsar==true){
                cout<<"Tienes escudo activado"<<endl;
                BalaE[i].activo=false;
            }else{
                Player.setSalud(Player.getSalud()-BalaE[i].potencia);
                al_play_sample(DeadNave, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                BalaE[i].activo=false;
            }
            PowerEscudo->paraUsar=false;
        }
        if(Colision(BalaE[i].x,BalaE[i].y,BalaE[i].bordeX,BalaE[i].bordeY,BalaE[i].destX,BalaE[i].destY,BalaE[i].destX+10,BalaE[i].destY+10)){
            BalaE[i].activo=false;

        }

    }
    return Player.getSalud();
}

//---------Func. Enemigos--------------------------------------
void InitEnemigos(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++){
        Enemy[i].activo = false;
    }
}
void LiberaEnemigos(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (!Enemy[i].activo) {
            if ((rand() % 1000) == 0) {
                Enemy[i].type = rand()%5+1;
                //Jets
                if(Enemy[i].type == 1){
                    Enemy[i].velocidad=4;
                    Enemy[i].bordeX=50;
                    Enemy[i].bordeY=50;
                    Enemy[i].potencia = 10;
                    Enemy[i].salud = 10;
                    Enemy[i].x = 60+ rand() % (650-120);
                    Enemy[i].y = 0;
                    Enemy[i].shot=true;
                    Enemy[i].activo = true;
                    break;
                }
                //Bombardero
                else if(Enemy[i].type == 2) {
                    Enemy[i].velocidad = 2;
                    Enemy[i].bordeX = 50;
                    Enemy[i].bordeY = 50;
                    Enemy[i].potencia = 30;
                    Enemy[i].salud = 20;
                    Enemy[i].x = 60 + rand() % (650 - 120);
                    Enemy[i].y = 0;
                    Enemy[i].shot=true;
                    Enemy[i].activo = true;
                    break;
                }
                //Torres
                else if(Enemy[i].type == 3){
                    Enemy[i].velocidad=0;
                    Enemy[i].bordeX=75;
                    Enemy[i].bordeY=75;
                    Enemy[i].potencia = 20;
                    Enemy[i].salud = 20;
                    Enemy[i].x = 60+ rand() % (650-120);
                    Enemy[i].y = 20+ rand() % (480-40);
                    Enemy[i].activo = true;
                    break;
                }
                //Torres de misiles
                else if(Enemy[i].type == 4){
                    Enemy[i].velocidad=0;
                    Enemy[i].potencia = 30;
                    Enemy[i].bordeX=75;
                    Enemy[i].bordeY=75;
                    Enemy[i].salud = 20;
                    Enemy[i].x = 60+ rand() % (650-120);
                    Enemy[i].y = 20+ rand() % (480-120);
                    Enemy[i].shot=true;
                    Enemy[i].activo = true;
                    break;
                }
                else if(Enemy[i].type == 5){
                    Enemy[i].velocidad=2;
                    Enemy[i].bordeX=100;
                    Enemy[i].bordeY=75;
                    Enemy[i].potencia = 0;
                    Enemy[i].salud = 20;
                    Enemy[i].x = 60+ rand() % (650-120);
                    Enemy[i].y = 0;
                    Enemy[i].shot= false;
                    Enemy[i].activo = true;
                    break;
                }
            }
        }
    }
}
void ActualizaEnemigos(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (Enemy[i].activo){
            Enemy[i].y += Enemy[i].velocidad;
            if (Enemy[i].y > 450)
                Enemy[i].activo= false;
        }
    }
}
void DibujaEnemigos(Enemigo Enemy[], int tamanho){
    for(int i=0;i< tamanho;i++) {
        if (Enemy[i].activo){
            if(Enemy[i].type==1) {
                Enemy1 = al_load_bitmap("images/Enemy3.png");
                al_draw_bitmap(Enemy1, Enemy[i].x, Enemy[i].y, ALLEGRO_FLIP_VERTICAL);
            }
            else if(Enemy[i].type==2) {
                Enemy1 = al_load_bitmap("images/Enemy1.png");
                al_draw_bitmap(Enemy1, Enemy[i].x, Enemy[i].y, 0);
            }
            else if(Enemy[i].type==3) {
                Enemy1 = al_load_bitmap("images/Tower2.png");
                al_draw_bitmap(Enemy1, Enemy[i].x, Enemy[i].y, 0);
            }
            else if(Enemy[i].type==4) {
                Enemy1 = al_load_bitmap("images/Tower1.png");
                al_draw_bitmap(Enemy1, Enemy[i].x, Enemy[i].y, 0);
            }
            else if(Enemy[i].type==5) {
                Enemy1 = al_load_bitmap("images/Enemy5.png");
                al_draw_bitmap(Enemy1, Enemy[i].x, Enemy[i].y, ALLEGRO_FLIP_VERTICAL);
            }
        }
    }
}
int EnemigoChoca(Enemigo Enemy[],PowerUpEscudo PowerEscudo[], int tamanho, Nave Player){
    for(int i=0; i< tamanho; i++) {
        if (Enemy[i].activo) {
            if (Colision(Enemy[i].x, Enemy[i].y, Enemy[i].bordeX, Enemy[i].bordeY, Player.getX() + 10, Player.getY() + 10, Player.getBordeX(), Player.getBordeY())) {
                if(PowerEscudo->paraUsar==true){
                    cout<<"Tienes escudo activado"<<endl;
                    Enemy[i].activo = false;

                }else{
                    Player.setVidas(Player.getVidas() - 1);
                    cout << "Te quedan: " << Player.getVidas() << " vidas" << endl;
                    al_play_sample(DeadNave,1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    Enemy[i].activo = false;
                }
                PowerEscudo->paraUsar=false;
            }

        }
    }
    return Player.getVidas();
}