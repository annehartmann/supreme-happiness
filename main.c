#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int button_size;
int num_buttons;

int button_index(int x_coordinate, int y_coordinate){ 

	//gets coordinates x, y; returns button index
	if ((button_size == 0) || (num_buttons == 0)){
		perror("neither button size nor number of buttons must be 0");
		return -1;
	}
	int index = (x_coordinate/button_size) + ((y_coordinate/button_size) * num_buttons);
	if (index >= (num_buttons * num_buttons)){
		perror("This should not happen. Complain to Anne.");
		return -1;
	}
	return index;
}

int main(void){

	SDL_Event e;
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

		while(SDL_PollEvent(&e)){ //handle events
			if (e.type == SDL_QUIT){//close window if "x" is pressed
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){ //listen for mouse clicks
				
				if (e.button.button == SDL_BUTTON_LEFT){ //left
					printf("clicked left at: %d, %d \n", e.button.x, e.button.y);
				}
				if (e.button.button == SDL_BUTTON_RIGHT){//right
					printf("clicked right at: %d, %d \n", e.button.x, e.button.y);
				}
			}
		
		}
	
	}


	SDL_DestroyWindow(window);
	SDL_Quit();	
	
	return 0;

}
