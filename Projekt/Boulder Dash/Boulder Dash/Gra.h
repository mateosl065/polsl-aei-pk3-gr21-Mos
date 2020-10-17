#ifndef GRA
#define GRA

#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

class Gra
{
	bool funkcjonuje;
	SDL_Window* okno;
	int licznik=0;

public:

	static SDL_Renderer* renderer;

	Gra();
	~Gra();

	void zainicjuj(const char* tytul , int x, int y, int szerokosc, int wysokosc, bool pelny_ekran);
	void operuj_wydarzeniami();
	void aktualizuj();
	void renderuj();
	void wyczysc();
	bool funkcjonuj();
};

#endif

