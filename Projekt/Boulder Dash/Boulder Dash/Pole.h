#ifndef POLE
#define POLE
#include "Gra.h"

class Pole
{
	int x,y;
	SDL_Texture* tekstura;
	SDL_Rect zrodloR, celR;
	
public:
	Pole(const char* nazwa_tekstury,int x, int y);
	~Pole();
	void aktualizuj();
	void renderuj();

};

#endif
