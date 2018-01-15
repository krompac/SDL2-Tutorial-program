#include <SDL.h>
#include "prozor.h"
#undef main;

int main()
{
	Prozor *pokreni = new Prozor;

	bool radi = true;

	while (radi)
	{
		radi = pokreni->zatvori_prozor();
		pokreni->postavi_sliku();
	}

	delete pokreni;

	return 0;
}