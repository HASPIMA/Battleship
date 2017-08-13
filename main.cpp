/*
	*(c) Harrison Pinto (HASPIMA), licencia MIT: http://es.wikipedia.org/wiki/MIT_License

ToDo:	menú
		guardar puntaje
		comentar el código

*/

#include "miniwin/miniwin.h"
#include "miniwin/Letras.hpp"
#include <sstream>



using namespace miniwin;
using namespace std;
#define Tamanhio_tablero 10
int tabBarcos1[Tamanhio_tablero][Tamanhio_tablero];
int tabBarcos2[Tamanhio_tablero][Tamanhio_tablero];
int tabDisp1  [Tamanhio_tablero][Tamanhio_tablero];
int tabDisp2  [Tamanhio_tablero][Tamanhio_tablero];

int tamC = 60;	  //tamaño de los cuadrados
int te;			 //captura la tecla presionada
int jugadas = 1;//utilizada para iterar entre jugadores

void tablero_vacio();

string i_to_str(int n){//convertir entero a un arreglo de caracteres
    stringstream sout;
    sout<<n;
    string ret = sout.str().c_str();
    return ret;
}

void m_juego(string msg){//Para ahorrarme el título :V
	mensaje("[UN] BATTLESHIP",msg);
}

void reset_Matrices(){//Reiniciar los valores de las matrices
	for(int x=0; x<Tamanhio_tablero;x++){
		for (int y = 0; y < Tamanhio_tablero; y++){
			tabBarcos1[x][y]= AZUL; //rellenar de vacío
			tabBarcos2[x][y]= AZUL; //rellenar de vacío
			tabDisp1  [x][y]= 0;	//rellenar de vacío
			tabDisp2  [x][y]= 0;	//rellenar de vacío
		}
	}
}

void conteo(string txt,int t_seg){//conteo regresivo
	if (t_seg <0){
		t_seg *= -1;
	}

	color(BLANCO);
	for (int i = t_seg; i >=0 ; i--){
		borra();
		texto(vancho()/4, valto()/4, txt);
		texto(vancho()/4+15*Tamanhio_tablero, valto()/4, i_to_str(i));
		refresca();
		espera(1000);
	}
}


struct cord{int x, y;};

struct Barco{
	int tam;
	cord origen;
	cord cabinas[4];
	int color_barco;

	void posicionar(int jg){
		cord tmp_ori= origen;
		color(color_barco);
		cord tmp_cab[4];
		for (int i = 0; i < 4; ++i){
			tmp_cab[i]=cabinas[i];
		}

		te=tecla();
		if(te==IZQUIERDA){//Girar contrario a las manecillas del reloj
			for(int i = 0; i<4; i++){
				int tmpX = cabinas[i].x;
				cabinas[i].x = -cabinas[i].y;
				cabinas[i].y = tmpX;

			}

		}
		if (te==DERECHA){//Girar en sentido de las manecillas del reloj
			for(int i = 0; i<4; i++){
				int tmpX = cabinas[i].x;
				cabinas[i].x = cabinas[i].y;
				cabinas[i].y = -tmpX;

			}

		}
		if(invalidarPosicion(jg)){
			for (int i = 0; i < 4; ++i){
				cabinas[i] = tmp_cab[i];
			} //corregir si el giro es erróneo
		}
		origen = {raton_x()/tamC, raton_y()/tamC}; //leer la posición del ratón
		if(invalidarPosicion(jg)){
			origen = tmp_ori;
		}
	}
	bool invalidarPosicion(int jugador){
		if (jugador == 1){
			if(origen.x > Tamanhio_tablero-1 ||
			  origen.x < 0 ||
			  origen.y > Tamanhio_tablero-1 ||
			  origen.y < 0 ||
			  (tabBarcos1[origen.x][origen.y] != AZUL)){ return true;}//Origen

			for(int i = 0; i < 4; i++){
				if(cabinas[i].x+origen.x > Tamanhio_tablero-1 ||
					cabinas[i].x+origen.x < 0 ||
					cabinas[i].y+origen.y > Tamanhio_tablero-1 ||
					(tabBarcos1[cabinas[i].x+origen.x][cabinas[i].y+origen.y] != AZUL) ||
					cabinas[i].y+origen.y < 0){return true;}//Cabinas
			}
		}
		if (jugador == 2){
			if(origen.x > Tamanhio_tablero-1 ||
			  origen.x < 0 ||
			  origen.y > Tamanhio_tablero-1 ||
			  origen.y < 0 ||
			  (tabBarcos2[origen.x][origen.y] != AZUL)){ return true;}//Origen

			for(int i = 0; i < 4; i++){
				if(cabinas[i].x+origen.x > Tamanhio_tablero-1 ||
					cabinas[i].x+origen.x < 0 ||
					cabinas[i].y+origen.y > Tamanhio_tablero-1 ||
					(tabBarcos2[cabinas[i].x+origen.x][cabinas[i].y+origen.y] != AZUL) ||
					cabinas[i].y+origen.y < 0){return true;}//Cabinas
			}
		}
		return false;
	}
	void pintar(){
		color(color_barco);
		rectangulo_lleno(origen.x*tamC+1,origen.y*tamC+1,origen.x*tamC+tamC,origen.y*tamC+tamC);//origen
		for(int i = 0; i<tam-1; i++){
			rectangulo_lleno((origen.x+cabinas[i].x)*tamC+1,(origen.y+cabinas[i].y)*tamC+1,
							 (origen.x+cabinas[i].x)*tamC+tamC,(origen.y+cabinas[i].y)*tamC+tamC);//cabinas
		}
	}

};

Barco Barcos1[7] = { { 5,{-1,1},{ {0,1},{0,2},{0,3},{0,4} }, AMARILLO }, //Portaviones
					 { 4,{-1,1},{ {0,1},{0,2},{0,3},{0,0} }, NARANJA  }, //fragata
					 { 4,{-1,1},{ {0,1},{0,2},{0,3},{0,0} }, NARANJA  }, //fragata
					 { 3,{-1,1},{ {0,1},{0,2},{0,0},{0,0} }, VERDE    }, //crucero
					 { 3,{-1,1},{ {0,1},{0,2},{0,0},{0,0} }, VERDE    }, //crucero
					 { 2,{-1,1},{ {0,1},{0,0},{0,0},{0,0} }, MAGENTA  }, //lancha
					 { 2,{-1,1},{ {0,1},{0,0},{0,0},{0,0} }, MAGENTA  }};//lancha
Barco Barcos2[7] = { { 5,{-1,1},{ {0,1},{0,2},{0,3},{0,4} }, AMARILLO }, //Portaviones
					 { 4,{-1,1},{ {0,1},{0,2},{0,3},{0,0} }, NARANJA  }, //fragata
					 { 4,{-1,1},{ {0,1},{0,2},{0,3},{0,0} }, NARANJA  }, //fragata
					 { 3,{-1,1},{ {0,1},{0,2},{0,0},{0,0} }, VERDE    }, //crucero
					 { 3,{-1,1},{ {0,1},{0,2},{0,0},{0,0} }, VERDE    }, //crucero
					 { 2,{-1,1},{ {0,1},{0,0},{0,0},{0,0} }, MAGENTA  }, //lancha
					 { 2,{-1,1},{ {0,1},{0,0},{0,0},{0,0} }, MAGENTA  }};//lancha



struct Jugador{
	int jug;

	void seleccionarNave(){
		borra();
		tablero_vacio();
		for(int i = 0; i<7; i++){
			do{
				if(jug == 1){
					Barcos1[i].posicionar(jug);
					for(int j = 0; j<7;j++)Barcos1[j].pintar();
				}
				if (jug == 2){
					Barcos2[i].posicionar(jug);
					for(int j = 0; j<7;j++)Barcos2[j].pintar();
				}
				refresca();
				espera(200);
				borra();
				pintarTablero();
			}while(!raton_boton_izq());
			tablero();
		}
	}
	void pintarTablero(){
		for(int i = 0; i<Tamanhio_tablero; i++){
			for(int j = 0; j<Tamanhio_tablero; j++){
				if(jug == 1){
					if(tabBarcos1[i][j] == AZUL) color(AZUL);//Lugar vacio
					else color(tabBarcos1[i][j]);
				}
				if ((jug == 2)){
					if(tabBarcos2[i][j] == AZUL) color(AZUL);//Lugar vacio
					else color(tabBarcos2[i][j]);
				}
				rectangulo_lleno(i*tamC+1,j*tamC+1,i*tamC+tamC,j*tamC+tamC);
			}
		}
	}
	void tablero(){ //guarda las posiciones de los barcos en las matrices con sus colores respectivos
		for(int i = 0; i<7; i++){
			if(jug == 1){
				tabBarcos1[Barcos1[i].origen.x][Barcos1[i].origen.y] = Barcos1[i].color_barco;//posición del origen
				for(int j = 0; j<4; j++)tabBarcos1[Barcos1[i].origen.x+Barcos1[i].cabinas[j].x][Barcos1[i].origen.y+Barcos1[i].cabinas[j].y] = Barcos1[i].color_barco;//posición de las cabinas
			}
			if ((jug == 2)){
				tabBarcos2[Barcos2[i].origen.x][Barcos2[i].origen.y] = Barcos2[i].color_barco;//posición del origen
				for(int j = 0; j<4; j++)tabBarcos2[Barcos2[i].origen.x+Barcos2[i].cabinas[j].x][Barcos2[i].origen.y+Barcos2[i].cabinas[j].y] = Barcos2[i].color_barco;//posición de las cabinas
			}
		}
	}
	void pintarDisparos(){
		for(int i = 0; i<Tamanhio_tablero; i++){
			for(int j = 0; j<Tamanhio_tablero; j++){
				if(jug == 1){
					if(tabDisp1[i][j]==2){//Disparo perdido
					   color(BLANCO);
					   circulo_lleno(i*tamC+tamC/2,j*tamC+tamC/2,tamC/4);
					}
					if(tabDisp1[i][j]==1){//Disparo acertado
						color(ROJO);
						circulo_lleno(i*tamC+tamC/2,j*tamC+tamC/2,tamC/4);
					}
				}
				if (jug == 2){
					if(tabDisp2[i][j]==2){//Disparo perdido
					   color(BLANCO);
					   circulo_lleno(i*tamC+tamC/2,j*tamC+tamC/2,tamC/4);
					}
					if(tabDisp2[i][j]==1){//Disparo acertado
						color(ROJO);
						circulo_lleno(i*tamC+tamC/2,j*tamC+tamC/2,tamC/4);
					}
				}

			}
		}
		refresca();
		espera(10);
	}
	void disparar(){
		bool no_dsp = true;
		while(no_dsp){
			if(raton_boton_izq()){
				if(jug == 1){
					if(tabBarcos2[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] != AZUL) tabDisp1[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] = 1;//si se acierta
					else tabDisp1[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] = 2;//si no se acierta
				}
				if ((jug == 2)){
					if(tabBarcos1[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] != AZUL) tabDisp2[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] = 1;//si se acierta
					else tabDisp2[(int)(raton_x()/tamC)][(int)(raton_y()/tamC)] = 2;//si no se acierta
				}
				no_dsp = false;
			}
		}
		pintarDisparos();
		while(te != ESPACIO){//permitir que el jugador vea los disparos hechos hasta presionar la barra espaciadora
			te=tecla();
			espera(10);
		}
		++jugadas;//aumentar para poder iterar entre jugadores
	}
	bool win(){
		int impactos=0;
		for (int i = 0; i < Tamanhio_tablero; i++){
			for (int j = 0; j < Tamanhio_tablero; j++){
				if(jug==1){
					if (tabDisp1[i][j]==1){//contar disparos acertados
						impactos++;
					}
				}
				if ((jug == 2)){
					if (tabDisp2[i][j]==1){//contar disparos acertados
						impactos++;
					}
				}
			}
		}
		return impactos==3;//Número de disparos necesarios para ganar
	}
};

Jugador Jug1 = {1};
Jugador Jug2 = {2};

void jugar();

int main(){
	vredimensiona(Tamanhio_tablero*tamC,Tamanhio_tablero*tamC);
	reset_Matrices();
	espera(50);

	jugar();

	refresca();
	espera(Tamanhio_tablero);
	//if(pregunta("[UN] BATTLESHIP","       ¿Deseas juegar nuevamente?\nDa click en Aceptar para iniciar nuevamente el juego.")) main();
	m_juego("Gracias por jugar");
	espera(Tamanhio_tablero*10);
	vcierra();
	return 0;
}

void tablero_vacio(){
	borra();
	color(AZUL);
	for(int i = 0; i<Tamanhio_tablero; i++){
		for(int j = 0; j<Tamanhio_tablero; j++){
			rectangulo_lleno(i*tamC+1,j*tamC+1,i*tamC+tamC,j*tamC+tamC);
		}
	}
	refresca();
	espera(10);
}

void jugar(){
	//posicionar las naves
	tablero_vacio();
	m_juego("Posiciona tus barcos Jugador 1");
	Jug1.seleccionarNave();
	Jug1.tablero();
	espera(1000);
	m_juego("Posiciona tus barcos Jugador 2");
	Jug2.seleccionarNave();
	Jug2.tablero();
	espera(1000);

	//Iniciar el juego
	m_juego("Una vez dispares podrás ver el tablero de juego. Tendrás que presionar la tecla ESPACIO para continuar y dejar de verlo");
	conteo("El juego inicia en:",5);
	do{
		tablero_vacio();
		if (jugadas%2!=0){
			Jug1.pintarDisparos();
			m_juego("Dispara el Jugador 1");
			espera(1000);
			te=tecla();
			Jug1.disparar();
		}
		else{
			Jug2.pintarDisparos();
			m_juego("Dispara el Jugador 2");
			espera(1000);
			te=tecla();
			Jug2.disparar();
		}
	}while (!(Jug1.win() || Jug2.win()));
	if(Jug1.win()){
		borra();
		Jug2.pintarTablero();//mostrar los barcos del adversario
		Jug1.pintarDisparos();//mostrar los impactos hechos
		m_juego("El Jugador 1 ha ganado");
	}
	else{
		borra();
		Jug1.pintarTablero();//mostrar los barcos del adversario
		Jug2.pintarDisparos();//mostrar los impactos hechos
		m_juego("El Jugador 2 ha ganado");
	}
}
