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
					
	int intentos;
	
	public:
	bool crearNave(int l, char tipo){
		bool flag = true;
		srand(time(NULL));
		//x fila, y columna
		int x = 1+ rand()%15; // 1 ~ 15
		int y = 2+ rand()%15; // 2 ~ 16
		
		int dir = rand()%4; // 0 Norte, 1 Sur, 2 Oeste, 3 Este
	
		switch (dir){
			case 0:
				//Comprueba que el barco cae en dicha dirección
				if(x-l<0) {
					flag = false;
				}else{
					//Comprueba que no hay otro barco
					for(int i=0; i<l ; i++) {
						if(t[x-i][y]!='~') flag= false;
					}
					if(flag){
						//Coloca los barcos
						printf("%d\n",dir);
						for(int i=0;i<l;i++){
							t[x-i][y]=tipo;
						}
					}
				}
				break;
			case 1:
				//Comprueba que el barco cae en dicha dirección
				if(x+l>16) {
					flag = false;
				}else{
					//Comprueba que no hay otro barco
					for(int i=0; i<l ; i++) {
						if(t[x+i][y]!='~') flag= false;
					}
					if(flag){
						//Coloca los barcos
						printf("%d\n",dir);
						for(int i=0;i<l;i++){
							t[x+i][y]=tipo;
						}
					}
				}
				break;
			case 2:
				//Comprueba que el barco cae en dicha dirección
				if(y-l<1) {
					flag = false;
				}else{
					//Comprueba que no hay otro barco
					for(int i=0; i<l ; i++) {
						if(t[x][y-i]!='~') flag= false;
					}
					if(flag){
						//Coloca los barcos
						printf("%d\n",dir);
						for(int i=0;i<l;i++){
							t[x][y-i]=tipo;
						}
					}
				}
				break;
			case 3:
				//Comprueba que el barco cae en dicha dirección
				if(y+l>17) {
					flag = false;
				}else{
					//Comprueba que no hay otro barco
					for(int i=0; i<l ; i++) {
						if(t[x][y+i]!='~') flag= false;
					}
					if(flag){
						//Coloca los barcos
						printf("%d\n",dir);
						for(int i=0;i<l;i++){
							t[x][y+i]=tipo;
						}
					}
				}
				break;
		}
		return flag;
	}
	
	void Imprimir(){
	    for(int i=0; i<17;i++){
			for(int j=0; j<18;j++) printf("%3c", t[i][j]);
			printf("\n");
		}
		printf("        1  2  3  4  5  6  7  8  9  10 11 12 13 14 15");
 	}
  
	Tablero();
};

Tablero::Tablero(){
	
	while(!crearNave(5,'5'));
    //Imprimir();
    while(!crearNave(4,'4'));
    while(!crearNave(4,'B'));
    //Imprimir();
    while(!crearNave(3,'3'));
    while(!crearNave(3,'S'));
    //Imprimir();
    while(!crearNave(1,'1'));
    while(!crearNave(1,'1'));
    while(!crearNave(1,'1'));
    Imprimir();
    
    intentos = 0;
}

int main(){
	
	Tablero tablita;
	return 0;
}
