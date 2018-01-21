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

	//inicijalizira se boja za renderer, postavlja se sve na nula
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

	//zadnja dva argumenta se mogu koristiti za neke pravokutnike, tj. prozore ili objekte
	//unutar glavnog prozora
	SDL_RenderCopy(global_renderer, global_texture, 0, 0);

	//update screen -> koristimo renderpresent jer više ne koristimo površinu nikakvu
	SDL_RenderPresent(global_renderer);

	/*
	postavljaju se koordinate nekog pravokutnog objekta kojeg imamo unutar prozora (x, y)
	i širina i visina (w, h)

	pravokutnik.x = 0;
	pravokutnik.y = 0;
	pravokutnik.w = 720;
	pravokutnik.h = 480;

	//koristi se ova f-ja da se rastegne neka učitana slika u neki okvir
	SDL_BlitScaled(slika, 0, povrsina, &pravokutnik);
	SDL_UpdateWindowSurface(prozor);*/
}

void Prozor::nacrtaj_pravokutnik()
{
	//inicijaliziramo varijablu u koju spremamo boju, tj. kod koji prikazuje neku boju
	Uint8 boja = 0xff;

	//ocisti prozor
	SDL_SetRenderDrawColor(global_renderer, boja, boja, boja, boja);
	SDL_RenderClear(global_renderer);

	//renderiraj, tj. nacrtaj neki pravokutnik, ispunjem bojom ( 4169e1 - plava) pravokutnik
	//postavljaju se širina, visina, x i y koordinate
	SDL_Rect ispunjen_pravokutnik = { width / 4, height / 4, width / 2, height / 2 };
	/* ili:
	pravokutnik.x = width / 4;
	pravokutnik.y = height / 4;
	pravokutnik.w = width / 2;
	pravokutnik.h = height / 2;
	*/

	//opet se ucitava boja u renderer
	SDL_SetRenderDrawColor(global_renderer, 0x70, 0x80, 0x90, boja);
	//postavljamo globalni renderer koji je gore ispunjen bojom u pravokutnik
	SDL_RenderFillRect(global_renderer, &ispunjen_pravokutnik);

	//postavljamo pravokutnik čiji obrub budemo crtali
	SDL_Rect vanjski_pravokutnik = { width / 6, height / 6, width * 2 / 3, height * 2 / 3};
	SDL_SetRenderDrawColor(global_renderer, 0xba, 0x55, 0xd3, boja);
	//crta se obrub pravokutnik gornjim rendererom
	SDL_RenderDrawRect(global_renderer, &vanjski_pravokutnik);


	SDL_SetRenderDrawColor(global_renderer, 0xdc, 0x14, 0x3c, boja);
	//crta se linija s bojom od ove f-je gore
	//argumenti su pocetni x, pocetni y, krajni x, krajnji y
	SDL_RenderDrawLine(global_renderer, 0, height / 2, width, height / 2);

	SDL_SetRenderDrawColor(global_renderer, 0x2e, 0x34, 0x8c, boja);
	int i = 0;
	for (i = 0; i < height; i+= 4)
	{
		//crtaju se točke na polovici ekrana, vertikalno
		SDL_RenderDrawPoint(global_renderer, width / 2, i);
	}

	//update screen
	SDL_RenderPresent(global_renderer);
}

