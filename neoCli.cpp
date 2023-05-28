#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <iostream>

// inet_addr
#include <arpa/inet.h>
#include <unistd.h>

// For threading, link with lpthread
#include <pthread.h>
#include <semaphore.h>

#define PUERTO 4747

using namespace std;

int main(){
    string mensaje = "esteeselmensaje";
    const char* mensaje_char = mensaje.c_str();
    int net_socket;

    //socket protocolo TCP
    net_socket = socket(AF_INET, SOCK_STREAM, 0);

    //inicializacion direccion IP y puerto
    struct sockaddr_in direccion_server;
    direccion_server.sin_family = AF_INET;
    direccion_server.sin_addr.s_addr = INADDR_ANY;
    direccion_server.sin_port = htons(PUERTO);

    //inicializar socket
    int conexion = connect(net_socket,(struct sockaddr*)&direccion_server,sizeof(direccion_server));
    
    //revisar error de conexion

    if(conexion < 0){
        cout << "ERROR EN LA CONEXION" << endl;
        return 0;
    }

    cout << "CONEXION EXITOSA" << endl;

    while (1)
    {
        cout << "Ingrese mensaje: ";
        cin >> mensaje;
        const char* mensaje_char = mensaje.c_str();
        send(net_socket, mensaje_char, mensaje.length(), 0);
    }
    
    close(net_socket);
}