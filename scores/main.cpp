#include <iostream>
#include <fstream>


using namespace std;

void guardar(char*,int);
void ordenar(char*, int);

int main(){
    char Nombre[50]="rata";
    int puntaje=567;

    ordenar(Nombre,puntaje);
}

void guardar(char* name,int puntaje){
    ofstream Guardar;
    Guardar.open("Datos.txt",ios::app);

    Guardar<<endl<<name<<" "<<puntaje<<endl;

}

void ordenar(char* nombre,int puntaje){
    FILE *miarchivo;
    char * archivo="Datos.txt";
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
        guardar(nprimero,num);
        guardar(nsegundo,num2);
        guardar(ntercero,num3);
        guardar(ncuarto,num4);
        guardar(nombre,puntaje);

    }else if (puntaje>num4 && puntaje<num3){
        guardar(nprimero,num);
        guardar(nsegundo,num2);
        guardar(ntercero,num3);
        guardar(nombre,puntaje);
        guardar(ncuarto,num4);

    }else if (puntaje>num3 && puntaje<num2){
        guardar(nprimero,num);
        guardar(nsegundo,num2);
        guardar(nombre,puntaje);
        guardar(ntercero,num3);
        guardar(ncuarto,num4);

    }else if (puntaje>num2 && puntaje<num){
        guardar(nprimero,num);
        guardar(nombre,puntaje);
        guardar(nsegundo,num2);
        guardar(ntercero,num3);
        guardar(ncuarto,num4);

    }else if (puntaje>num){
        guardar(nombre,puntaje);
        guardar(nprimero,num);
        guardar(nsegundo,num2);
        guardar(ntercero,num3);
        guardar(ncuarto,num4);

    }else{
        guardar(nprimero,num);
        guardar(nsegundo,num2);
        guardar(ntercero,num3);
        guardar(ncuarto,num4);
        guardar(nquinto,num5);

    }


}
