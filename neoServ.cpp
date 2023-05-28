// C program for the Server Side
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

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

int main(){
    int server_socket, new_socket, mensaje_recibido, valread;
    struct sockaddr_in direccion_server;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    char buffer[8192] = { 0 };

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
    while (1)
    {
        valread = read(new_socket, buffer, 8192);
        cout << "Mensaje Entrante "<< buffer << endl;
    }
    
    close(new_socket);
    shutdown(server_socket, SHUT_RDWR);
    return 0;

}