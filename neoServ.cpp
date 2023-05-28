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
    Tablero cpu;

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

    void Enviar(){
        //Formateo de mensaje
        mensaje.clear();
        for (int i = 0; i < 17; i++)
        {   
            for (int j = 0; j < 18; j++)
            {
                temp = cpu.tVisible[i][j];
                mensaje.append(temp);
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
};

int main(){

    srand(time(NULL));
    Server servidor;

    servidor.CrearSocket();

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
    
    servidor.CerrarSocket();
    return 0;
}