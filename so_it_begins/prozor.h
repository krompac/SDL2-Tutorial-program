#pragma once
#include <SDL.h>
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

	public:
		//na temelju inputa iz funkcije prikazi strelice preuzima strelicu koja se bude prikazala
		SDL_Surface * ucitaj_strelice(KeyPressSurfaces uvjet);
		//koristi input tipke iz zatvori_prozor da prikaze sliku
		void prikazi_strelice();
		//drzi otvoren prozor tak dugo dok ne stisnem x gore
		//inace se koristi za input po kojem se prikazuju strelice
		bool zatvori_prozor();
		//glavna f-ja za prozor
		void glavna();

		Prozor() : prozor(NULL), povrsina(NULL), slika(NULL) { this->glavna(); };

		void close();
		SDL_Surface *ucitaj_sliku(std::string ime);
};

