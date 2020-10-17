#include <SDL.h>
#include "Gra.h"

Gra* gra = nullptr;

int main(int argc, char*argv[])
{
	const int FPS=60;
	const int opuznienie_klatki = 1000 / FPS;
	Uint32 start_klatki;
	int czas_klatki;

	gra = new Gra();
	gra->zainicjuj("Boulder Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640,false);
	while(gra->funkcjonuj())
	{
		start_klatki=SDL_GetTicks();

		gra->operuj_wydarzeniami();
		gra->aktualizuj();
		gra->renderuj();
	
		czas_klatki = SDL_GetTicks() - start_klatki;
		if (opuznienie_klatki > czas_klatki)
			SDL_Delay(opuznienie_klatki - czas_klatki);
	}
	gra->wyczysc();
	return 0;
}