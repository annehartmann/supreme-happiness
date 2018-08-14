#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int main(void){

	SDL_Window *window;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_RESIZABLE
	);
	
	if (window == NULL){
		printf("could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Delay(3000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;

}
