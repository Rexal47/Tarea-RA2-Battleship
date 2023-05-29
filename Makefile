#Compilar los dos programas
all: TAREARA2

#Compila los dos archivos
TAREARA2:
	g++ neoServ.cpp -o neoServ
	g++ neoCli.cpp -o neoCli

#Compila solo servidor
neoServ.cpp:
	g++ neoServ.cpp -o neoServ

#Compila solo cliente
neoCli.cpp:
	g++ neoCli.cpp -o neoCli

clean: 
	rm neoServ
	rm neoCli
