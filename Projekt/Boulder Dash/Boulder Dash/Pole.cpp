#include "Pole.h"
#include "MenedzerTekstur.h"

Pole::Pole(const char* nazwa_tekstury, int x,int y)
{
	tekstura = MenedzerTekstur::wczytaj_teksture(nazwa_tekstury);
	this->x = x;
	this->y = y;
}

Pole::~Pole()
{

}

void Pole::aktualizuj()
{
	x++;
	y++;

	zrodloR.h = 16;
	zrodloR.w = 16;
	zrodloR.x = 0;
	zrodloR.y = 0;

	celR.h = zrodloR.h*4;
	celR.w = zrodloR.w*4;
	celR.x = x;
	celR.y = y;
}

void Pole::renderuj()
{
	SDL_RenderCopy(Gra::renderer, tekstura, &zrodloR, &celR);

}