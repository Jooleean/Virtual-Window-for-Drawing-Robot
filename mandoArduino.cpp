#include "SerialClass.h"
#include <iomanip> // para precision de floats en string
#include <sstream> // para mezclar variables en strings
#include "iostream"

#define DELAY 500

char recibido = 'N';

void mensajeParaArduino(Serial* Arduino, std::string mensaje)
{

	if (Arduino->IsConnected())
	{
		Arduino->WriteData((char*)mensaje.c_str(), mensaje.length());

		std::cout << "esperando... ";

		while (recibido != 'K')
		{
			Arduino->ReadData(&recibido, 1);
		}

		std::cout << "Mensaje entregado correctamente\n";
     	recibido = 'N';


		char recepcionAngulos[256];
		bool completado = false;

		while (!completado)
		{
			int bytesLeidos = Arduino->ReadData(recepcionAngulos, 255);

			if (bytesLeidos > 0)
			{
				recepcionAngulos[bytesLeidos] = '\0'; 
				std::cout << recepcionAngulos; 

				if (strchr(recepcionAngulos, 'm')) {
					completado = true;
					
				}
			}
		}

		std::cout << ".........................\n";

	}
}



