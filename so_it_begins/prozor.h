#pragma once

//TODO: napraviti klasu s ovim f-jama za prozor

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

//drzi otvoren prozor tak dugo dok ne stisnem x gore ili stisnem gumb na tipkovnici ili mišu
bool zatvori_prozor()
{
	SDL_Event dogadjaj;

	while (SDL_PollEvent(&dogadjaj))
	{
		switch (dogadjaj.type)
		{
			case SDL_QUIT:
				return true;
			case SDL_MOUSEBUTTONDOWN:
				return true;
			case SDL_KEYDOWN:
				return true;
		}

		return false;
	}
}

//zatvara i dealocira svu memoriju koja se koristi za prozore
void close(SDL_Surface *povrsina, SDL_Window *prozor)
{
	SDL_FreeSurface(povrsina);
	povrsina = NULL;

	SDL_DestroyWindow(prozor);
	prozor = NULL;

	SDL_Quit();
}

//glavna f-ja za prozor
void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Greška: " << SDL_GetError() << std::endl;

		return;
	}

	SDL_Window *prozor = SDL_CreateWindow("Prozor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1300, 720, SDL_WINDOW_SHOWN);
	
	if (!prozor)
	{
		std::cout << "Greška: " << SDL_GetError() << std::endl;
		
		return;
	}

	SDL_Surface *povrsina = SDL_GetWindowSurface(prozor);
	SDL_Surface *slika = SDL_LoadBMP("neka.bmp");

	if (slika == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;

		close(slika, prozor);

		return;
	}

	SDL_BlitSurface(slika, 0, povrsina, 0);
	SDL_UpdateWindowSurface(prozor);


	while (true)
	{
		if (zatvori_prozor())
		{
			close(slika, prozor);
			return;
		}
	}
}
