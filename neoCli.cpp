#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>
#include "Tablero.hpp"

// inet_addr
#include <arpa/inet.h>
#include <unistd.h>

// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>

#define PUERTO 4747
#define IP "172.28.61.242"

using namespace std;

class Client{

    std::string mensaje, temp;
    struct sockaddr_in direccion_server;
    int net_socket, conexion, valread, i, j, k;
    char buffer[8192] = { 0 };

    public:
    Tablero player;
    void CrearSocket(){
        net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //inicializacion direccion IP y puerto
    
        direccion_server.sin_family = AF_INET;
        direccion_server.sin_addr.s_addr = inet_addr(IP);
        direccion_server.sin_port = htons(PUERTO);
    }

    void Conectar(){
        //inicializar socket
        conexion = connect(net_socket,(struct sockaddr*)&direccion_server,sizeof(direccion_server));
    
        //revisar error de conexion

        if(conexion < 0){
            cout << "ERROR EN LA CONEXION" << endl;
            return;
        }

        cout << "CONEXION EXITOSA" << endl;
    }

    void Enviar(){
        //Formateo de mensaje
        mensaje.clear();
        for (int i = 0; i < 17; i++)
        {   
            for (int j = 0; j < 18; j++)
            {
                temp = player.tVisible[i][j];
                mensaje.append(temp);
            }
        }
        
        const char* mensaje_char = mensaje.c_str();
        send(net_socket, mensaje_char, mensaje.length(), 0);
    }

    void Recibir(){
        valread = read(net_socket, buffer, 8192);
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
        close(net_socket);
    }
};

int main(){
    
    srand(time(NULL));
    Client cliente;

    cliente.CrearSocket();
    cliente.Conectar();

    //Game Loop
    while (1)
    {
        //server indica que es el turno del cliente para disparar
        //cliente indica coordenadas, las envia
        //server recibe coordenadas y envia tablero con resultados
        //cliente indica que es el turno del server para disparar
        //server indica coordenadas, las envia
        //cliente recibe coordenadas y envia tablero con resultados
    }

    cliente.CerrarSocket();
    return 0;
}