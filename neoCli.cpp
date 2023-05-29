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

    //Variables a utlizar
    std::string mensaje, temp;
    struct sockaddr_in direccion_server;
    int net_socket, conexion, valread, i, j, k, x, y;
    
    char tDisparos[17][18];
    char tJugador[17][18];

    public:
    char buffer[8192] = { 0 };
    std::string coordenadas;
    Tablero tablero;

    //inicializacion direccion IP y puerto
    void CrearSocket(){
        net_socket = socket(AF_INET, SOCK_STREAM, 0);    
        direccion_server.sin_family = AF_INET;
        direccion_server.sin_addr.s_addr = inet_addr(IP);
        direccion_server.sin_port = htons(PUERTO);
    }

    //Conexion con el servidor
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

    //Envia coordenadas de disparo al servidor
    void EnviarCoord(string coordenada){
        const char* mensaje_char = coordenada.c_str();
        send(net_socket, mensaje_char, coordenada.length(), 0);
    }

    //Recibe informacion del servidor
    void Recibir(){
        valread = read(net_socket, buffer, 8192);
    }

    //Se imprime el tablero de disparos y el propio
    void ImprimirTablero(int tablero){
        int k = tablero;
        printf("\n");
        for (size_t i = 0; i < 17; i++)
        {
            for (size_t j = 0; j < 18; j++)
            {
                if(tablero == 0){
                    tDisparos[i][j] = buffer[k];
                }else{
                    tJugador[i][j] = buffer[k];
                }
                printf("%3c", buffer[k]);
                k++;
            }
            printf("\n");
        }
        printf("\n        1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");
    }

    //Le pone la cabecera a cada tablero
    void FormatearTableros(){
        //Primer tablero empieza desde el 0 en buffer
        cout << "Mar enemigo" << endl;
        ImprimirTablero(0);
        //Primer tablero empieza desde el 306 en buffer
        cout << "Tus barcos" << endl;
        ImprimirTablero(306);
    }

    //Cerrar conexion con el servidor
    void CerrarSocket(){
        close(net_socket);
    }

    //Input para enviar al servidor
    void InputTablero(){
        std::string posicion;
        bool flag = true;
        string coord;
			//leemos y validamos la coordenada
			while(flag){
				flag=false;
				printf("Ingresa coordenada (ejemplo: A-1 o A,1 ): ");
				//leemos la coordenada
				getline(cin,coord);
				//validamos que no exceda el limite de caracteres
				if(coord.length()<3 || coord.length()>4) {
					printf("Por favor, sigue el formato Letra-Numero (A-1) o Letra,Numero (A,1).\n");
					flag=true;	
				}else{
					//Transformamos la letra a numero, si no esta entre la letra A y O, responde -1
					x=idLetra(toupper(coord[0]));
					if(x==-1) {
						printf("Letra fuera del rango.\n");
						flag=true;	
					}else{
						//Revisa si se dividio el numero con el formato indicado
						if(coord[1]!=',' && coord[1]!='-') {
							printf("Recuerda dividir las coordenadas con '-' o ',' \n");
							flag = true;	
						}else{
							//revisa si despues de la "-" o ",", sigue un numero o un par de numeros
							if(!isdigit(coord[2]) || (coord.length()==4 && !isdigit(coord[3]))) {
								printf("Revisa si ingresaste un numero valido.\n");
								flag = true;	
							}else{
								if(coord.length()==3){
									y=atoi(coord.substr(2,1).c_str())+1;
								}else{
									y= atoi(coord.substr(2,2).c_str())+1;
								}
								//Comprueba que el disparo esta dentro de los margenes del tablero (x se valido anteriormente)
						    	if(y<2 || y>16){
						    		printf("Revisa si ingresaste una coordenada valida.\n");
						    		flag = true;
								}else{
									//Comprueba que no ha tirado a dicha posicion
									if(tDisparos[x][y]== 'X'){
						    			printf("Ya has tirado a esta posicion.\n");
						    			flag = true;
									}
								}
							}	
						}
					}
				}
			}
        posicion.clear();
        if(x<10){
            posicion = "0" + std::to_string(x);
        }else{
            posicion = std::to_string(x);
        }
        if(y<10){
            posicion = posicion + "0" + std::to_string(y);
        }else{
            posicion = posicion + std::to_string(y);
        }
        cout << coord << "coord" << endl;
        cout << posicion << "coordenadas" << endl;
        EnviarCoord(posicion);
    }

    //Retorna el valor numerico de la letra
	int idLetra(char letra){
		int numero=0;
		switch (letra){
			case 'A':
				numero=1;
				break;
			case 'B':
				numero=2;
				break;
			case 'C':
				numero=3;
				break;
			case 'D':
				numero=4;
				break;
			case 'E':
				numero=5;
				break;
			case 'F':
				numero=6;
				break;
			case 'G':
				numero=7;
				break;
			case 'H':
				numero=8;
				break;
			case 'I':
				numero=9;
				break;
			case 'J':
				numero=10;
				break;
			case 'K':
				numero=11;
				break;
			case 'L':
				numero=12;
				break;
			case 'M':
				numero=13;
				break;
			case 'N':
				numero=14;
				break;
			case 'O':
				numero=15;
				break;
			default:
				numero=-1;
				break;
		}
		return numero;
	}

};


int main(){
    //variables que se utilizan
    string msg_server, msg_control;
    //Creacion de instancia de cliente y su conexion
    Client cliente;
    cliente.CrearSocket();
    cliente.Conectar();

    //Recibe tableros de disparos y con sus barcos
    cliente.Recibir();
    msg_server = cliente.buffer;
    cliente.FormatearTableros();
    msg_control= msg_server.substr(msg_server.length()-6,6).c_str();

    //Loop de juego principal
    while (msg_control != "winsrv" && msg_control != "winjug")
    {
        
        //Turno de jugador
        if(msg_control == "111111"){
            cout << "Turno del Jugador" << endl;
            cliente.InputTablero();
            cliente.Recibir();
            system("clear");
        }else{
            //Turno del CPU
            cout << "Turno del CPU" << endl;
            cliente.Recibir();
            cliente.FormatearTableros();
        }
        //Se formatea la informacion recibida para que sea leida por el siguiente loop
        msg_server = cliente.buffer;
        msg_control= msg_server.substr(msg_server.length()-6,6).c_str();
    }

    //Mensaje de finalizacion de juego
    if(msg_control == "winsrv"){
        cout << "HA GANADO EL CPU..." << endl;
    }else{
        cout << "HAS GANADO!" << endl;
    }

    //Terminar conexion
    cliente.CerrarSocket();
    return 0;

}