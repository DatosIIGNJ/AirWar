#include <iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main()
{
    int client, server;
    int portnum = 8081;
    bool isExit = false;
    int bufsize = 256;
    char buffer[bufsize];
    char contentBuffer[bufsize-1];
    struct sockaddr_in server_addr,client_addr;
    socklen_t size;
    int n;
    //init socekt
    server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0){
        cout << "Error Estableciendo la conexion" << endl;
    }
    cout <<"server Socket conexion creada" << endl;
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portnum);

    //biding soket
    if(bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0){
        cout << "Error Biding Socket" << endl;
        exit(1);
    }

    cout << "buscando clientes" << endl;
    listen(server,1);//escuchando sokets
    size= sizeof(client_addr);
    //accept client
    client = accept(server, (struct sockaddr*)&client_addr, &size);
    if(client< 0){
        cout<< "Error al Aceptar" << endl;
        exit(1);
    }
    while(server >0){
        //strcpy(buffer,"server conectado---\n");
        //send(server,buffer,bufsize,0);
        cout <<"conectado con el cliente" << endl;
        cout <<"Esperando mensaje de cliente... "<<endl;
        bzero(buffer,256);
        bzero(contentBuffer,255);
        n = read(client,buffer,255 );
        if (n < 0)
        {
            perror("ERROR reading from socket");
            return(1);
        }
        strncpy(contentBuffer,buffer,strlen(buffer) - 1);
        cout<<"Mensaje: "<<endl;
        cout<<buffer;
        if (n < 0)
        {
            perror("ERROR writing to socket");
            return(1);
        }else if(n==6){
            cout<<"Avion hacia la izquierda"<<endl;
        }else if(n==7){
            cout<<"Avion hacia la derecha"<<endl;
        }
    }
    close(server);
    return 0;
}