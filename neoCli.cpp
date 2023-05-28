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
#define IP "192.168.1.120"

using namespace std;

class Client{

    std::string mensaje, temp;
    struct sockaddr_in direccion_server;
    int net_socket, conexion, valread, i, j, k, x, y;
    
    char tDisparos[17][18];
    char tJugador[17][18];

    public:
    char buffer[8192] = { 0 };
    std::string coordenadas;
    Tablero tablero;
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
        // mensaje.clear();
        // for (int i = 0; i < 17; i++)
        // {   
        //     for (int j = 0; j < 18; j++)
        //     {
        //         temp = player.tVisible[i][j];
        //         mensaje.append(temp);
        //     }
        // }
        
        // cout  << mensaje << endl;
        // const char* mensaje_char = mensaje.c_str();
        // send(net_socket, mensaje_char, mensaje.length(), 0);
    }

    void Recibir(){
        valread = read(net_socket, buffer, 8192);
    }

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

    void FormatearTableros(){
        //Primer tablero empieza desde el 0 en buffer
        cout << "Tablero Disparos" << endl;
        ImprimirTablero(0);
        //Primer tablero empieza desde el 306 en buffer
        cout << "Tablero Barcos" << endl;
        ImprimirTablero(306);
    }

    void CerrarSocket(){
        close(net_socket);
    }

    //input para enviar al servidor
    void InputTablero(){
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
        if(x<10){
            coordenadas = "0" + std::to_string(x);
        }else{
            coordenadas = std::to_string(x);
        }
        if(y<10){
            coordenadas = coordenadas + "0" + std::to_string(y);
        }else{
            coordenadas = coordenadas + std::to_string(y);
        }
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
    
    srand(time(NULL));
    Client cliente;
    cliente.CrearSocket();
    cliente.Conectar();
    //Recibe tableros de disparos y con sus barcos
    //cliente.Recibir();
    //cliente.FormatearTableros();

    //cliente.InputTablero();
    cliente.Recibir();
    cout << cliente.buffer << endl;
    cout << cliente.coordenadas << endl;

    //Recibe tableros de disparos y con sus barcos
    //cliente.Recibir();
    //cliente.FormatearTableros();

    //cliente.InputTablero();
    cliente.Recibir();
    cliente.FormatearTableros();

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

    //cliente.CerrarSocket();
    return 0;

}