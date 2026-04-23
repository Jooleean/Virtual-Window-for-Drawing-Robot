#pragma once
#include <string>

class Coordenadas {
public:
	float x;
	float y;
	float z;
};

class Punto {

public:
	Coordenadas coordDesdeEsquina;
	Coordenadas coordDesdeCentro;
	Coordenadas coordMundoReal;
	std::string mensaje;
	int color;
};