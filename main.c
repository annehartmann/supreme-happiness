#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int button_index(int x_coordinate, int y_coordinate){ 
	//gets coordinates x, y; returns button index
	if ((button_size == 0) || (num_buttons == 0)){
		perror("neither button size nor number of buttons must be")
	}
	int index = (x_coordinate/button_size) + ((y_coordinate/button_size) * num_buttons);
	return index;
}

int main(void){

	SDL_Event event;
	bool quit = false;
	int button_size = 50;//size of a button in pixels
	int num_buttons = 15; //number of buttons in one row/column
	int index; //index of a button

	SDL_Window *window; //create a window
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(button_size * num_buttons),
		(button_size * num_buttons),
		SDL_WINDOW_RESIZABLE
	);
	
	if (window == NULL){ //prints error and quits program if window creation fails
		printf("could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	while (!quit){ //listen for events until user quits program by closing window

		while(SDL_PollEvent(&event)){ //handle events
			if (event.type == SDL_QUIT){//close window if "x" is pressed
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN){ //listen for mouse clicks
				
				if (event.button.button == SDL_BUTTON_LEFT){ //left
					printf("left\n");
				}
				if (event.button.button == SDL_BUTTON_RIGHT){//right
					printf("right\n");
				}
			}
		
		}
	
	}


	SDL_DestroyWindow(window);
	SDL_Quit();	
	
	return 0;

}
