#include "prozor.h"

void Prozor::close()
{
	SDL_FreeSurface(povrsina);
	povrsina = NULL;

	SDL_DestroyWindow(prozor);
	prozor = NULL;

	SDL_Quit();
}

SDL_Surface * Prozor::ucitaj_sliku(std::string ime)
{
	SDL_Surface *picture = SDL_LoadBMP(ime.c_str());

	if (picture == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}

	return picture;
}

SDL_Surface * Prozor::ucitaj_strelice(KeyPressSurfaces uvjet)
{
	SDL_Surface* slike_tipki[TOTAL];

	switch (uvjet)
	{
		case UP:
			slike_tipki[UP] = ucitaj_sliku("strelice/gore.bmp");
			break;
		case DOWN:
			slike_tipki[DOWN] = ucitaj_sliku("strelice/dole.bmp");
			break;
		case LEFT:
			slike_tipki[LEFT] = ucitaj_sliku("strelice/levo.bmp");
			break;
		case RIGHT:
			slike_tipki[RIGHT] = ucitaj_sliku("strelice/desno.bmp");
			break;
		default:
			slike_tipki[DEFAULT] = ucitaj_sliku("strelice/default.bmp");
			break;
	}

	return slike_tipki[uvjet];
}

void Prozor::prikazi_strelice()
{
	SDL_Surface *slika = NULL;

	switch (tipka.key.keysym.sym)
	{
		case SDLK_UP:
			slika = ucitaj_strelice(UP);
			break;
		case SDLK_DOWN:
			slika = ucitaj_strelice(DOWN);
			break;
		case SDLK_RIGHT:
			slika = ucitaj_strelice(RIGHT);
			break;
		case SDLK_LEFT:
			slika = ucitaj_strelice(LEFT);
			break;
		default:
			slika = ucitaj_strelice(DEFAULT);
			break;
	}

	SDL_BlitSurface(slika, 0, povrsina, 0);
	SDL_UpdateWindowSurface(prozor);
}

bool Prozor::zatvori_prozor()
{
	while (SDL_PollEvent(&tipka))
	{
		if (tipka.type == SDL_QUIT)
		{
			close();
			return false;
		}
		else //if (tipka.type == SDL_KEYDOWN)
		{
			prikazi_strelice();
			return true;
		}
	}

	return true;
}

void Prozor::glavna()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Greška: " << SDL_GetError() << std::endl;

		return;
	}

	//prozor u kojem se bude odvijal celi program
	prozor = SDL_CreateWindow("Prozor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN);

	if (!prozor)
	{
		std::cout << "Greška: " << SDL_GetError() << std::endl;

		return;
	}

	//povrsina od prozora
	povrsina = SDL_GetWindowSurface(prozor);

	//pocetna slika da bude default
	slika = ucitaj_strelice(DEFAULT);
	SDL_BlitSurface(slika, 0, povrsina, 0);
	SDL_UpdateWindowSurface(prozor);


	bool delaj = true;

	//PLAY tak dugo dok nema X
	while (delaj)
	{
		delaj = zatvori_prozor();
	}
}

