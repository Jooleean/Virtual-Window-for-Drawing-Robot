#include "SerialClass.h"
#define DELAY 500

void DatosaArduino(Serial* Arduino, int largoCadena, char display[100][8])
{
	Sleep(500);
	if (Arduino->IsConnected())
	{
		for (int i = 0; i < largoCadena; i++)
		{
			Arduino->WriteData((char*)display[i], 7);
			Sleep(DELAY - 10);
		}
	}
}