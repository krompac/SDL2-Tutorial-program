#include "prozor.h"

Prozor::~Prozor()
{
	SDL_FreeSurface(povrsina);
	povrsina = NULL;

	SDL_DestroyWindow(prozor);
	prozor = NULL;

	SDL_Quit();
	IMG_Quit();
}

SDL_Texture * Prozor::ucitaj_sliku(std::string ime)
{
	SDL_Surface *picture = IMG_Load(ime.c_str());
	SDL_Texture *textura = NULL;

	if (picture == NULL)
	{
		std::cout << "ERROR: " << SDL_GetError() << std::endl;
	}
	else
	{
		//napravi se textura prek slike koja bude išla u renderer da se prikaže
		textura = SDL_CreateTextureFromSurface(global_renderer, picture);
		
		if (!textura)
			std::cout << "Greška kod pravljenja texture!\nError: " << SDL_GetError() << std::endl;

		//makne se prvo učitana slika
		SDL_FreeSurface(picture);
	}

	return textura;
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

	//radi se renderer za prozor
	//argumenti su prozor kojem se bude nekaj željeno renderalo
	//zatim index, općenito je za neki driver koji koristimo za renderanje (ako znamo)
	//al po defaultu je -1 (prvi dostupni za ono kaj nam treba)
	//zadnji argument je zastava (enum) koji nam veli kaj renderer koristi
	//accelerated koristi naš hardware
	global_renderer = SDL_CreateRenderer(prozor, -1, SDL_RENDERER_ACCELERATED);

	if (!global_renderer)
	{
		std::cout << "Greška kod renderanja!\n" << SDL_GetError() << std::endl;
		return;
	}

	//inicijalizira se boja za renderer
	//argumenti: renderer, red, green, blue i alpha -> to guglaj ak ti nije jasno
	SDL_SetRenderDrawColor(global_renderer, 0xff, 0xff, 0xff, 0xff);

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
	this->global_texture = ucitaj_sliku("tiger.png");

	if (!this->global_texture)
	{
		std::cout << "Bila je greška!\n";
		return;
	}

	//očisti ekran od prijašnjeg renderera
	SDL_RenderClear(global_renderer);

	//"renderiraj" texturu na ekran
	//zadnja dva argumenta se mogu koristiti za neke pravokutnike, tj. prozore ili objekte
	//unutar glavnog prozora
	SDL_RenderCopy(global_renderer, global_texture, 0, 0);

	//update screen -> koristimo renderpresent jer više ne koristimo površinu nikakvu
	SDL_RenderPresent(global_renderer);

	/*
	pravokutnik.x = 0;
	pravokutnik.y = 0;
	pravokutnik.w = 720;
	pravokutnik.h = 480;

	//koristi se ova f-ja da se rastegne neka slika u neki okvir
	SDL_BlitScaled(slika, 0, povrsina, &pravokutnik);
	SDL_UpdateWindowSurface(prozor);*/
}

