#include "MenedzerTekstur.h"

SDL_Texture* MenedzerTekstur::wczytaj_teksture(const char* nazwa_tekstury)
{
	SDL_Surface* plaszczyzna = IMG_Load(nazwa_tekstury);
	SDL_Texture* tekstura= SDL_CreateTextureFromSurface(Gra::renderer, plaszczyzna);
	SDL_FreeSurface(plaszczyzna);
	return tekstura;
}