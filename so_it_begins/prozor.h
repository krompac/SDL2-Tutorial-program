#pragma once

//TODO: napraviti klasu s ovim f-jama za prozor

//custom made događaji koji se koriste da bi bilo jasnije (recimo)
//svaka po defaultu ima vrijednost od 0 do nekog broja (u ovom slucaju TOTAL ima 5 (6. je))
enum KeyPressSurfaces
{
	DEFAULT,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	TOTAL
};

//zatvara i dealocira svu memoriju koja se koristi za prozore
void close(SDL_Surface *povrsina, SDL_Window *prozor)
{
	SDL_FreeSurface(povrsina);
	povrsina = NULL;

	SDL_DestroyWindow(prozor);
	prozor = NULL;

	SDL_Quit();
}

SDL_Surface *ucitaj_sliku(std::string ime)
{
	SDL_Surface *picture = SDL_LoadBMP(ime.c_str());

	if (picture == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}

	return picture;
}

SDL_Surface *ucitaj_strelice(KeyPressSurfaces uvjet)
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

void prikazi_strelice (SDL_Surface *povrsina, SDL_Window *prozor, SDL_Event &tipka) 
{
	//povrsina koja ucitava u sebe sliku
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

//drzi otvoren prozor tak dugo dok ne stisnem x gore ili stisnem gumb na tipkovnici ili mišu
bool zatvori_prozor(SDL_Surface *povrsina, SDL_Window *prozor)
{
	SDL_Event dogadjaj;

	while (SDL_PollEvent(&dogadjaj))
	{
		if (dogadjaj.type == SDL_QUIT)
		{
			close(povrsina, prozor);
			return false;
		}
		else// if (dogadjaj.type == SDL_KEYDOWN)
		{
			prikazi_strelice(povrsina, prozor, dogadjaj);
			return true;
		}
	}

	return true;
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

	//prozor u kojem se bude odvijal celi program
	SDL_Window *prozor = SDL_CreateWindow("Prozor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 480, SDL_WINDOW_SHOWN);
	
	if (!prozor)
	{
		std::cout << "Greška: " << SDL_GetError() << std::endl;
		
		return;
	}

	//povrsina od prozora
	SDL_Surface *povrsina = SDL_GetWindowSurface(prozor);

	//pocetna slika da bude default
	SDL_Surface *pocetna = ucitaj_strelice(DEFAULT);
	SDL_BlitSurface(pocetna, 0, povrsina, 0);
	SDL_UpdateWindowSurface(prozor);

	bool delaj = true;

	while (delaj)
	{
		delaj = zatvori_prozor(povrsina, prozor);
	}
}
