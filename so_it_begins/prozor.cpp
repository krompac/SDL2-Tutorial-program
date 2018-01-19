#include "prozor.h"

Prozor::~Prozor()
{
	SDL_FreeSurface(povrsina);
	povrsina = NULL;

	SDL_DestroyWindow(prozor);
	prozor = NULL;

	SDL_Quit();
}

SDL_Surface* Prozor::ucitaj_sliku(std::string ime)
{
	SDL_Surface *picture = IMG_Load(ime.c_str());
	SDL_Surface *optimizirana_slika = NULL;

	if (picture == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}
	else
	{
		//pretvori sliku da bude zadovoljila format ekrana
		optimizirana_slika = SDL_ConvertSurface(picture, povrsina->format, NULL);
		if (!optimizirana_slika)
			std::cout << "Greška kod optimizacije slike!\nError: " << SDL_GetError() << std::endl;

		//makne se prvo učitana slika
		SDL_FreeSurface(picture);
	}

	return optimizirana_slika;
}

bool Prozor::zatvori_prozor()
{
	while (SDL_PollEvent(&tipka))
	{
		if (tipka.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}

void Prozor::init()
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

	//inicijalizacija učitavanja slike (..._PNG je tip slike koji budemo učitali)
	imgFlags = IMG_INIT_PNG;
	//img init ucitava iz biblioteka funkcije za učitavanje slike, prima parametar za zastavice
	//po kojoj zna za koju sliku
	//if provjerava jel je to uspelo, ak nije ispisuje grešku
	if (!IMG_Init(imgFlags) && imgFlags)
	{
		std::cout << "Greška: " << IMG_GetError() << std::endl;
		return;
	}

	//povrsina od prozora
	povrsina = SDL_GetWindowSurface(prozor);
}

void Prozor::postavi_sliku()
{
	this->slika = ucitaj_sliku("tiger.png");

	if (!this->slika)
	{
		std::cout << "Bila je greška!\n";
		return;
	}

	pravokutnik.x = 0;
	pravokutnik.y = 0;
	pravokutnik.w = 720;
	pravokutnik.h = 480;

	//koristi se ova f-ja da se rastegne neka slika u neki okvir
	SDL_BlitScaled(slika, 0, povrsina, &pravokutnik);
	SDL_UpdateWindowSurface(prozor);
}

