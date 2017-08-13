/*
 *Coded by: Sebastián Garnica Quiroz

*/


#include "miniwin.h"
#include <string>


struct Letter{
	bool mapa[8][5];
				//pos x,pos y, tam x, tam y,  degradado
	void pintar(int x, int y, int xt, int yt, double deg){
	}
};
// Declaracion de todas las letras del abecedario
Letter todas[26];
		// pos x, pos y, cadena de char, tamañoX, tamañoY, pix entre letraas, degradado, coordenadas en medio
void d_text(int x, int y, const std::string& s, int xt, int yt, int esp, double deg, bool xMedio){}  // Funcion que pinta un caracter con el tamaño que uno desee

