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
        //inicializacion direccion IP y puerto
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
	    direccion_server.sin_addr.s_addr = INADDR_ANY;
	    direccion_server.sin_family = AF_INET;
	    direccion_server.sin_port = htons(PUERTO);

        bind(server_socket,(struct sockaddr*)&direccion_server,sizeof(direccion_server));

        //escuchando clientes entrantes
        if (listen(server_socket, 3) == 0)
            printf("Listening\n");
        else
            printf("Error\n");

        addr_size = sizeof(serverStorage);
        //Se acepta cliente
        new_socket = accept(server_socket,(struct sockaddr*)&direccion_server,&addr_size);
        if(new_socket <0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        cout << "NUEVA CONEXION" << endl;
    }

    //Envia informacion de juego
    void Enviar(Tablero jug, Tablero srv, bool turnoJugador){
        //Formateo de mensaje
        mensaje.clear();
        //tviSible tjugaodr win+quiengana

        for (int i = 0; i < 17; i++)
        {   
            for (int j = 0; j < 18; j++)
            {
                temp = srv.tVisible[i][j];
                //temp = srv.tRespuestas[i][j];
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
                if(turnoJugador){
                    mensaje.append("111111");
                }else{
                    mensaje.append("000000");
                }
                
            } 
        }

        const char* mensaje_char = mensaje.c_str();
        send(new_socket, mensaje_char, mensaje.length(), 0);
    }

    //Recibe informacion del cliente
    void Recibir(){
        valread = read(new_socket, buffer, 8192);
    }

    //Se cierra conexion con cliente
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
    Enviar(player, cpu, turnoPlayer);

    /*ACA PONER EL ENVIO DEL TABLERO [~] y [R] +WINS+QUIENGANA*/

    //Seguira el juego mientras ninguno gane
    while (!cpu.ganar(true) && !player.ganar(false))
    {
        if(turnoPlayer){
            /*ENVIAR MENSAJE DE QUE ES TURNO DEL JUGADOR*/
            /*ACA RECIBIR X E Y*/
            Recibir();
            string coord = buffer;

            x=atoi(coord.substr(0,2).c_str());
            y=atoi(coord.substr(2,2).c_str());

            cpu.calcularDisparo(x,y,true);
            turnoPlayer = false;
          
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

            turnoPlayer = true;
        }

        /*ACA PONER EL ENVIO DEL TABLERO [~] y [R] +WINS+QUIENGANA*/
        Enviar(player, cpu, turnoPlayer);
    }

}
};

int main(){

    //Creacion de instancia servidor
    srand(time(NULL));
    Server servidor;

    //Se crea el socket de conexion
    servidor.CrearSocket();

    //Se inicia el loop de juego principal
    servidor.juego();

    cout << "CONEXION CERRADA" << endl;
    
    servidor.CerrarSocket();
    return 0;
}