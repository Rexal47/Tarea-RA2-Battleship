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
	// 0 indica que disparo fuera de los limites, 
	// 1  indica que disparo correctamente, 
	// -1  indica que ya habia disparado a esa posicion 
	int disparo(int x, int y, bool jugador){ 
		//Comprueba que el disparo esta dentro de los margenes del tablero
    	if(x<1 || x>15 || y<2 || y>16){
    		printf("Has disparado en una posicion equivocada.\n");
    		return 0;
		} 
    	
    	//Comprueba que no ha tirado a dicha posicion
    	if(tRespuestas[x][y]== 'X') {
    		printf("Ya has tirado a esta posicion.\n");
    		return -1;
		}
		//Creamos un auxiliar para facilitar el entendimiento del codigo
    	char aux=tRespuestas[x][y];
    	
    	if(tRespuestas[x][y]!=' ') {
			//Ve si le ha dado a un portaaviones o una lancha
			if(aux=='P' || aux=='L'){
				if(aux=='P'){
					portaaviones--;
					if(portaaviones>0) {
						printf("Le has dado a un portaavion.\n");
					}else{
						printf("Has hundido un portaavion.\n");
					}
				}else{
					lancha--;
					printf("Has hundido una lancha.\n");
				}
				tVisible[x][y]=aux;
			}else{
				//Comprueba si le ha dado a un buque
				if(aux== 'B' || aux== '8'){
					if(aux=='B'){
						buque1--;
						if(buque1>0) {
							printf("Le has dado a un buque (1).\n");
						}else{
							printf("Has hundido un buque (1).\n");
						}
					}else{
						buque2--;
						if(buque2>0) {
							printf("Le has dado a un buque (2).\n");
						}else{
							printf("Has hundido un buque (2).\n");
						}
					}
					tVisible[x][y]='B';
				}else{
					//Comprueba si le ha dado a un submarino
					if(aux=='S'){
						submarino1--;
						if(submarino1>0) {
							printf("Le has dado a un submarino (1).\n");
						}else{
							printf("Has hundido un submarino (1).\n");
						}
					}else{
						submarino2--;
						if(submarino2>0) {
							printf("Le has dado a un submarino (2).\n");
						}else{
							printf("Has hundido un submarino (2).\n");
						}
					}
					tVisible[x][y]='S';
				}
			}		
    	}else{
    		tVisible[x][y]='X';
    		printf("Disparo fallido.\n");
		}
    	tRespuestas[x][y]='X';	
    	return 1;
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

int devolverNumero(char letra);

//int main(){
//	//Variable para crear el azar
//	srand(time(NULL));
////	for(int i=0;i<100;i++) dale(rand()%10);
//	Tablero tablita;
//	char x[1];
//	int fila, columna;
//	
//	int i=0;
//	while(i<5){
//		
//		tablita.Imprimir(true);
//		tablita.Imprimir(false);
//		
//		printf("Ingresa Fila: ");
//		scanf("%s",x);
//		printf("Ingresa Columna: ");
//		scanf("%d",&columna);
//		
//		fila = devolverNumero(x[0]);
////		y = atoi(cord.substr(2,1).c_str()) +1;
//		
//		//printf("Coordenadas: %d - %d\n",fila,columna+1);
//		
//		tablita.disparo(fila,columna+1);
//		i++;
//	}
//	
//	
//	return 0;
//}

int devolverNumero(char letra){
	
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
			numero=100;
			break;
	}
	return numero;
}

#endif

/*Falta -> f(x) ganar
si es disparo CPU, no mostrar print? o mostrar quien dispara
validar disparos (dividir por - en letra y número) = letra no leida error/letra leida buena / numero weno, numero malo, f(x) valida :)

*/
