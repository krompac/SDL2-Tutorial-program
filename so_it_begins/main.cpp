#include <SDL.h>
#include <SDL_image.h>
#include "prozor.h"
#undef main;

int main()
{
	Prozor *pokreni = new Prozor;

	bool radi = true;

	while (radi)
	{
		radi = pokreni->zatvori_prozor();

		if (radi)
			pokreni->render_objekt();
		else
		{
			break;
		}
	}
	

	delete pokreni;

	return 0;
}