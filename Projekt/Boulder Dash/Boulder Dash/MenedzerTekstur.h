#ifndef MENEDZER_TEKSTUR
#define MENEDZER_TEKSTUR

#include "Gra.h"

class MenedzerTekstur
{
public:
	static SDL_Texture* wczytaj_teksture(const char* nazwa_tekstury);
};

#endif