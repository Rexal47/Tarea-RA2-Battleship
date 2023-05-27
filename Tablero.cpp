#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

using namespace std;

class Tablero{
	
	char t[17][18]={{' ','X','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','X'}, 
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
	int portaaviones, buque1, buque2, submarino1, submarino2, lancha1, lancha2, lancha3;
	
	bool crearNave(int l, char tipo, int x,int y, int dir){
		
		//Dir: 0 Norte, 1 Sur, 2 Oeste, 3 Este
		//Comprueba que el barco cae en la posición
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
		
		//Comprueba si hay espacio para poner el barco
		for(int i=0; i<l ; i++) {
			if(dir<2){
				if(dir==0 && t[x-i][y]!='~') {
					return false;
				}
				if(dir==1 && t[x+i][y]!='~') {
					return false;
				}
			}else{
				if(dir==2 && t[x][y-i]!='~') {
					return false;
				}
				if(dir==3 && t[x][y+i]!='~') {
					return false;
				}
			}
		}
		
		//Coloca los barcos
		for(int i=0; i<l ; i++) {
			if(dir<2){
				if(dir==0){
					t[x-i][y]=tipo;
				}else{
					t[x+i][y]=tipo;
				}
			}else{
				if(dir==2 ){
					t[x][y-i]=tipo;
				}else{
					t[x][y+i]=tipo;
				}
			}
		}
		return true;
	}
	
	char disparo(int x, int y){
		//Comprueba que el disparo esta dentro de los margenes del tablero
    	if(x<1 || x>15 || y<2 || y>16) return 0;
    	char aux = t[x][y];
    	if(aux!= '~') t[x][y]='X';
    	return aux;
  }
	
	void Imprimir(){
	    for(int i=0; i<17;i++){
			for(int j=0; j<18;j++) printf("%3c", t[i][j]);
			printf("\n");
		}
		printf("        1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n\n");
		system("pause");
 	}
 	
	Tablero();
};

Tablero::Tablero(){
	
	//Variable para crear el azar
	srand(time(NULL));
	
	// crearNave(largo del barco, caracter del barco, eje X, eje Y, direccion del barco)
	while(!crearNave(5,'P',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(4,'B',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(4,'B',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(3,'S',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(3,'S',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
//    Imprimir();
    while(!crearNave(1,'L',1+ rand()%15, 2+ rand()%15,rand()%4));
    Imprimir();
    
    portaaviones = 5; 
	buque1 = 4;
	buque2 = 4;
	submarino1 = 3;
	submarino2 = 3;
	lancha1 = 1; 
	lancha2 = 1; 
	lancha3 = 1;
}

void dale(int a);

int main(){
//	srand(time(NULL));
//	for(int i=0;i<100;i++) dale(rand()%10);
	Tablero tablita[100];
	
	
	tablita[0].Imprimir() ;
	
	tablita[1].Imprimir() ;
	
	return 0;
}

void dale(int a){
	cout << a<<"\n";
}
