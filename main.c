#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int main(void){

	SDL_Event event;
	bool quit = false;

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
	
	while (!quit){

		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = true;
			}
			if (event.type == SDL_KEYDOWN){
				printf("key down\n");
			}
		
		}
	
	}


	SDL_DestroyWindow(window);
	SDL_Quit();	
	
	return 0;

}
