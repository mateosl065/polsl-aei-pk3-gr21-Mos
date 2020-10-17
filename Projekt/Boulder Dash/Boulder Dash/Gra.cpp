#include "Gra.h"
#include "MenedzerTekstur.h"
#include "Pole.h"

SDL_Renderer *Gra::renderer=nullptr;
Pole* gracz;

Gra::Gra()
{}

Gra::~Gra()
{}

void Gra::zainicjuj(const char* tytul, int x, int y, int szerokosc, int wysokosc, bool pelny_ekran)
{
	int flagi = 0;
	if (pelny_ekran)
	{
		flagi = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "zainicjowano"<<std::endl;
		okno = SDL_CreateWindow(tytul, x, y, szerokosc, wysokosc, flagi);
		if (okno)
			std::cout << "okno" << std::endl;
		renderer = SDL_CreateRenderer(okno, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer" << std::endl;
		}
		funkcjonuje = true;
	}
	else
		funkcjonuje = false;

	gracz = new Pole("assets/gracz.png",0,0);
}


void Gra::operuj_wydarzeniami()
{
	SDL_Event wydarzenie;
	SDL_PollEvent(&wydarzenie);
	
	switch (wydarzenie.type)
	{
	case SDL_QUIT:
		funkcjonuje = false;
		break;
	default:
		break;
	}
}

void Gra::aktualizuj()
{
	gracz->aktualizuj();
}

void Gra::renderuj()
{
	SDL_RenderClear(renderer);
	gracz->renderuj();
	SDL_RenderPresent(renderer);
}

void Gra::wyczysc()
{
	SDL_DestroyWindow(okno);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "wyczyszczono" << std::endl;
}

bool Gra::funkcjonuj()
{
	return funkcjonuje;
}