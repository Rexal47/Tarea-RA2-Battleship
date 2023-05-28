// C program for the Server Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include "Tablero.hpp"

// inet_addr
#include <arpa/inet.h>

// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PUERTO 4747
using namespace std;

class Server{
    std::string mensaje,temp;
    int server_socket, new_socket, mensaje_recibido, valread, k;
    struct sockaddr_in direccion_server;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[8192] = { 0 };

    public:
    void CrearSocket(){
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
	    direccion_server.sin_addr.s_addr = INADDR_ANY;
	    direccion_server.sin_family = AF_INET;
	    direccion_server.sin_port = htons(PUERTO);

        bind(server_socket,(struct sockaddr*)&direccion_server,sizeof(direccion_server));

        //escuchando equipos entrantes
        if (listen(server_socket, 3) == 0)
            printf("Listening\n");
        else
            printf("Error\n");

        addr_size = sizeof(serverStorage);
        new_socket = accept(server_socket,(struct sockaddr*)&direccion_server,&addr_size);
        if(new_socket <0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
    }

    void Enviar(Tablero jug, Tablero srv){
        //Formateo de mensaje
        mensaje.clear();
        //tviSible tjugaodr win+quiengana

        for (int i = 0; i < 17; i++)
        {   
            for (int j = 0; j < 18; j++)
            {
                temp = srv.tVisible[i][j];
                mensaje.append(temp);
            }
        }

        for (int i = 0; i < 17; i++)
        {   
            for (int j = 0; j < 18; j++)
            {
                temp = jug.tRespuestas[i][j];
                mensaje.append(temp);
            }
        }

        //Si el server gana por un jugador que es true, retorna true
        if(srv.ganar(true) == true){
            mensaje.append("winsrv");
        } else{
            if(jug.ganar(false) == true){
                mensaje.append("winjug");
            }else{
                mensaje.append("000000");
            } 
        }
        
        
        
        const char* mensaje_char = mensaje.c_str();
        send(new_socket, mensaje_char, mensaje.length(), 0);
    }

    void Recibir(){
        valread = read(new_socket, buffer, 8192);
    }

    void ImprimirTableroDisparos(){
        k=0;
        printf(" \n");
        for (size_t i = 0; i < 17; i++)
        {
            for (size_t j = 0; j < 18; j++)
            {
                printf("%3c", buffer[k]);
                k++;
            }
            printf("\n");
        }
        printf("\n        1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");
    }

    void CerrarSocket(){
        close(new_socket);
        shutdown(server_socket, SHUT_RDWR);
    }

    void juego(){

    //Indica si es el turno del jugador
    bool turnoPlayer;
    //Crea los tableros de cada jugador
    Tablero cpu, player;
    //Si es 0 empieza servidor, si es 1, jugador
    if(rand()%2==1){
        turnoPlayer = true;
    }else{
        turnoPlayer = false;
    }
    //X e Y son las posiciones donde se disparara
    int x=0,y=0;
    cout << "e llegao";
    Enviar(player, cpu);
    /*ACA PONER EL ENVIO DEL TABLERO [~] y [R] +WINS+QUIENGANA*/

    //Seguira el juego mientras ninguno gane
    while (!cpu.ganar(true) && !player.ganar(false))
    {
        if(turnoPlayer){
            /*ENVIAR MENSAJE DE QUE ES TURNO DEL JUGADOR*/
            /*ACA RECIBIR X E Y*/
            string coord;

            x=atoi(coord.substr(0,2).c_str());
            y=atoi(coord.substr(2,2).c_str())+1;

            cpu.calcularDisparo(x,y,true);
        }else{
            /*ENVIAR MENSAJE DE QUE ES TURNO DEL CPU + [!]*/

            //Genera un disparo en X,Y
            x= 1 + rand()%15;
			y= 2 + rand()%15;
            while (player.tRespuestas[x][y]=='X')
            {
                x= 1 + rand()%15;
			    y= 2 + rand()%15;
            }
            player.calcularDisparo(x,y,false);
        }

        /*ACA PONER EL ENVIO DEL TABLERO [~] y [R] +WINS+QUIENGANA*/
    }
    
}
};

int main(){

    srand(time(NULL));
    Server servidor;

    servidor.CrearSocket();

    servidor.juego();

    //Game Loop
    // while (1)
    // {
    //     //server indica que es el turno del cliente para disparar
    //     //cliente indica coordenadas, las envia
    //     //server recibe coordenadas y envia tablero con resultados
    //     //cliente indica que es el turno del server para disparar
    //     //server indica coordenadas, las envia
    //     //cliente recibe coordenadas y envia tablero con resultados
    // }
    
    servidor.CerrarSocket();
    return 0;
}