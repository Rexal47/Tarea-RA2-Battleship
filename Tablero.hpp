#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>
#ifndef TABLERO_HPP
#define TABLERO_HPP

using namespace std;

class Tablero{

	//Tablero con las posiciones de los barcos
	char tRespuestas[17][18]={{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}, 
					{'A','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'B','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'C','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'D','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'E','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'F','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'G','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'H','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'I','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'J','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'K','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'L','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'M','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'N','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{'O','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
					{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}};
					
	public:
	//Tablero visible por el jugador
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
		
	//Valores que indican si el barco esta hundido o no (>0 flotando, =0 hundido)			
	int portaaviones, buque1, buque2, submarino1, submarino2, lancha;
	
	//Funcion que ubica las naves (Largo nave, caracter representativo, pos x, pos y, direccion)
	bool crearNave(int l, char tipo, int x,int y, int dir){
		
		//Dir: 0 Norte, 1 Sur, 2 Oeste, 3 Este
		//Comprueba que el barco cae en la posicion
		if(dir<2){
			if(dir==0 && x-l<0) {
				return false;
			}
			if(dir==1 && x+l>15) {
				return false;
			}
		}else{
			if(dir==2 && y-l<1) {
				return false;
			}
			if(dir==3 && y+l>16) {
				return false;
			}
		}
		
		//Comprueba si hay espacio libre para poner el barco
		for(int i=0; i<l ; i++) {
			if(dir<2){
				if(dir==0 && tRespuestas[x-i][y]!=' ') {
					return false;
				}
				if(dir==1 && tRespuestas[x+i][y]!=' ') {
					return false;
				}
			}else{
				if(dir==2 && tRespuestas[x][y-i]!=' ') {
					return false;
				}
				if(dir==3 && tRespuestas[x][y+i]!=' ') {
					return false;
				}
			}
		}
		
		//Coloca los barcos
		for(int i=0; i<l ; i++) {
			if(dir<2){
				if(dir==0){
					tRespuestas[x-i][y]=tipo;
				}else{
					tRespuestas[x+i][y]=tipo;
				}
			}else{
				if(dir==2 ){
					tRespuestas[x][y-i]=tipo;
				}else{
					tRespuestas[x][y+i]=tipo;
				}
			}
		}
		return true;
	}
	
	//return:
	// True  indica que disparo correctamente, 
	// False indica que disparo incorrectamente
	bool calcularDisparo(int x, int y, bool jugador){ 
		
		//Creamos un auxiliar para facilitar el entendimiento del codigo
    	char aux=tRespuestas[x][y];
    	string nombrePlayer;
    	if(jugador) nombrePlayer="Jugador";
    	else nombrePlayer= "CPU";
    	
    	if(tRespuestas[x][y]!=' ') {
			//Ve si le ha dado a un portaaviones o una lancha
			if(aux=='P' || aux=='L'){
				if(aux=='P'){
					portaaviones--;
					if(portaaviones>0) {
						cout <<nombrePlayer <<" le ha dado a un portaavion.\n";
					}else{
						cout <<nombrePlayer <<" ha hundido un portaavion.\n";
					}
				}else{
					lancha--;
					cout <<nombrePlayer <<" ha hundido una lancha.\n";
				}
				tVisible[x][y]=aux;
			}else{
				//Comprueba si le ha dado a un buque
				if(aux== 'B' || aux== '8'){
					if(aux=='B'){
						buque1--;
						if(buque1>0) {
								cout <<nombrePlayer <<" le ha dado a un buque (1).\n";
						}else{
							cout <<nombrePlayer <<" ha hundido un buque (1).\n";
						}
					}else{
						buque2--;
						if(buque2>0) {
							cout <<nombrePlayer <<" le ha dado a un buque (2).\n";
						}else{
							cout <<nombrePlayer <<" ha hundido un buque (2).\n";
						}
					}
					tVisible[x][y]='B';
				}else{
					//Comprueba si le ha dado a un submarino
					if(aux=='S'){
						submarino1--;
						if(submarino1>0) {
							cout <<nombrePlayer <<" le ha dado a un submarino (1).\n";
						}else{
							cout <<nombrePlayer <<" ha hundido un submarino (1).\n";
						}
					}else{
						submarino2--;
						if(submarino2>0) {
							cout <<nombrePlayer <<" le ha dado a un submarino (2).\n";
						}else{
							cout <<nombrePlayer <<" ha hundido un submarino (2).\n";
						}
					}
					tVisible[x][y]='S';
				}
			}		
    	}else{
    		tVisible[x][y]='X';
    		cout <<nombrePlayer <<" ha fallado el disparo.\n";
		}
    	tRespuestas[x][y]='X';	
    	return true;
  }
	
	//imprime en pantalla: False tablero con respuestas, T tablero jugador
	void Imprimir(bool visible){
		if(visible){
			for(int i=0; i<17;i++){
				for(int j=0; j<18;j++) printf("%3c", tVisible[i][j]);
					printf("\n");
			}
		}else{
			for(int i=0; i<17;i++){
				for(int j=0; j<18;j++) printf("%3c", tRespuestas[i][j]);
					printf("\n");
			}
		}
		printf("        1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");
//		system("pause");
 	}
 	
 	//Manda el mensaje del ganador (True->Gana jugador, False->Gana CPU)
 	bool ganar(bool jugador){
 		if (portaaviones==0 && buque1 ==0 && buque2 == 0 && submarino1 ==0 && submarino2==0 && lancha==0){
 			if(jugador) printf("\nFELICIDADES JUGADOR, HAS GANADO.\n");
 			else printf("\nLAMENTABLEMENTE JUGADOR, HAS PERDIDO.\n");
 			return true;
		 }
		return false;
	 }
 	
 	//Genera el disparo para el caso del CPU o lee el disparo y lo valida para el jugador
 	bool disparo(bool user){
	
		bool flag=true;
		int x,y;
		if(user){
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
									if(tRespuestas[x][y]== 'X'){
						    			printf("Ya has tirado a esta posicion.\n");
						    			flag = true;
									}
								}
							}	
						}
					}
				}
			}
			return calcularDisparo(x,y,true);
		}else{
			//En caso de ser CPU, simplemente dispara a una posici�n al azar
			while(flag){
				flag=false;
				x= 1 + rand()%15;
				y= 2 + rand()%15;
				//Valida que no haya disparado a esa posici�n
				if(tRespuestas[x][y]== 'X'){
	    			flag = true;
				}
			}
			return calcularDisparo(x,y,false);
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
 	
	Tablero();
};

Tablero::Tablero(){

	// crearNave(largo del barco, caracter del barco, eje X, eje Y, direccion del barco)
	while(!crearNave(5,'P',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(4,'B',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(4,'8',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(3,'S',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(3,'5',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
    
    //Asigna los valores vida de un barco
    portaaviones = 5; 
	buque1 = 4;
	buque2 = 4;
	submarino1 = 3;
	submarino2 = 3;
	//Lancha vale 3 porque son 3 barcos de 1 de vida
	lancha = 3; 
}


#endif
