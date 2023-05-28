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
#define IP "172.28.61.242"

using namespace std;

class Client{

    std::string mensaje, temp;
    struct sockaddr_in direccion_server;
    int net_socket, conexion, i, j;

    char tVisible[17][18]={{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}, 
					{'A','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'B','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'C','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'D','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'E','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'F','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'G','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'H','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'I','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'J','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'K','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'L','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'M','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'N','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{'O','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
					{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}};
    public:
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
                temp = tVisible[i][j];
                mensaje.append(temp);
            }
        }
        
        const char* mensaje_char = mensaje.c_str();
        send(net_socket, mensaje_char, mensaje.length(), 0);
    }

    void Recibir(){
        
    }

    void CerrarSocket(){
        close(net_socket);
    }
};

int main(){
    Client cliente;

    cliente.CrearSocket();
    cliente.Conectar();
    cliente.Enviar();
    cliente.CerrarSocket();
    return 0;
    //string mensaje = "esteeselmensaje", temp;
    //const char* mensaje_char = mensaje.c_str();
    //int net_socket, i;

    //socket protocolo TCP
    // net_socket = socket(AF_INET, SOCK_STREAM, 0);

    // //inicializacion direccion IP y puerto
    
    // direccion_server.sin_family = AF_INET;
    // direccion_server.sin_addr.s_addr = inet_addr(IP);
    // direccion_server.sin_port = htons(PUERTO);

    // //inicializar socket
    // conexion = connect(net_socket,(struct sockaddr*)&direccion_server,sizeof(direccion_server));
    
    //revisar error de conexion

    // if(conexion < 0){
    //     cout << "ERROR EN LA CONEXION" << endl;
    //     return 0;
    // }

    // cout << "CONEXION EXITOSA" << endl;

    // char tVisible[17][18]={{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}, 
	// 				{'A','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'B','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'C','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'D','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'E','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'F','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'G','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'H','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'I','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'J','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'K','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'L','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'M','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'N','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{'O','|','~','~','~','~','~','~','~','~','~','~','~','~','~','~','~','|'},
	// 				{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}};


    //Formateo de mensaje
    // mensaje.clear();
    // for (int i = 0; i < 17; i++)
    // {   
    //     for (int j = 0; j < 18; j++)
    //     {
    //         temp = tVisible[i][j];
    //         mensaje.append(temp);
    //     }
    // }
    
    // const char* mensaje_char = mensaje.c_str();
    // send(net_socket, mensaje_char, mensaje.length(), 0);


    //send(net_socket, tVisible, sizeof(tVisible), 0);

    // while (1)
    // {
    //     cout << "Ingrese mensaje: ";
    //     cin >> mensaje;
    //     const char* mensaje_char = mensaje.c_str();
    //     send(net_socket, mensaje_char, mensaje.length(), 0);
    // }
    
}