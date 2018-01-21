#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

//TODO: promeniti glavnu f-ju (stavi ju u main f-ju kod main.cpp) i destruktor
class Prozor
{
	private:
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

		SDL_Surface *povrsina, *slika;
		SDL_Window *prozor;
		SDL_Event tipka;

		//renderer je zapravo nekaj u kaj se spremaju postupci renderinga
		//rendering je postupak prikazivanja slike na kompu
		SDL_Renderer *global_renderer;

		//globalna textura u koju budemo učitavali texture koje se kasnije
		//budu prikazivale prek renderera
		SDL_Texture *global_texture;

		//flag je predefinirani bit ili niz bitova koji sadrza binarnu vrijednost
		//u ovom našem slučaju, program inicijalizira zastavicu da zna predati to funkciju
		//po enumaratoru i da funkcija
		int imgFlags;

		const int width = 720;
		const int height = 480;

		SDL_Rect pravokutnik;
	public:
		//drzi otvoren prozor tak dugo dok ne stisnem x gore
		bool zatvori_prozor();
		//inicijalna f-ja za prozor
		void init();
		//postavi sliku
		void postavi_sliku();
		//funkcija za nacrtati pravokutnik prek renderera u prozoru
		void nacrtaj_pravokutnik();


		Prozor() : prozor(NULL), povrsina(NULL), slika(NULL) , global_renderer(NULL)
		{ 

			this->init(); 
		}
		~Prozor();

		SDL_Texture *ucitaj_sliku(std::string ime);
};

