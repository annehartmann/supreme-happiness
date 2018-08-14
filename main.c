#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int button_size;
int num_buttons;

int button_index(int x_coordinate, int y_coordinate, int num_of_buttons, int b_size){ 

	//gets coordinates x, y; returns button index
	//note that indices start at 1
	if ((b_size == 0) || (num_of_buttons == 0)){
		perror("neither button size nor number of buttons must be 0");
		return -1;
	}
	int index = (x_coordinate/b_size) + ((y_coordinate/b_size) * num_of_buttons);
	if ((index >= (num_of_buttons * num_of_buttons)) || (index < 0)){
		perror("This should not happen. Complain to Anne.");
		return -1;
	}
	return index;
}

void reveal(int button_index, int num_of_buttons){
	//reveals number/mine of field button_index

	//if this doesn't work check how booleans are treated during recursion

	//might be necessary to mark revealed fields with 10

	int number;// = look up number in array
	//booleans noting which neighbors the field has
	bool no_upper = true;
	bool no_lower = true;
	bool no_right = true;
	bool no_left = true;
	
	switch(number){
		case -1:
			//BOOM
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			//reveal number
			break;
		case 0:
			//reveal empty field
			//set array to '10' or something else marking field as revealed
			//recursively call reveal on neighbors
			if ((button_index% num_of_buttons) != 0){
				//field has left neighbor
				reveal(button_index - 1, button_index);
				no_left = false;
			} 
			if ((button_index%num_of_buttons) != (num_of_buttons - 1)){
				//field has right neighbor
				reveal(button_index + 1, num_of_buttons);
				no_right = false;
			}
			if (button_index >= num_of_buttons){
				//field has upper neighbor
				reveal(button_index - num_of_buttons, num_of_buttons);
				no_upper = false;
			}
			if (button_index < (num_of_buttons * (num_of_buttons - 1))){
				//field has lower neighbor
				reveal(button_index + num_of_buttons, num_of_buttons);
				no_lower = false;
			}
			if (!no_left && !no_upper){
				//field has upper left neighbor
				reveal(button_index - (num_of_buttons + 1), num_of_buttons);
			}
			if (!no_upper && !no_right){
				//field has upper right neighbor
				reveal(button_index - num_of_buttons + 1, num_of_buttons);
			}
			if (!no_left && !no_lower){
				//field has lower left neighbor
				reveal(button_index + (num_of_buttons - 1), num_of_buttons);
			}
			if (!no_lower && !no_right){
				//field has lower right neighbor
				reveal(button_index + num_of_buttons + 1, num_of_buttons);
			}
			break;
		case 10: //necessary to avoid creating infinite loop of neighboring empty fields calling reveal on each other 
			//marks revealed field
			break;
		default:
			perror("This should not happen. Complain to Anne.");
	}
	

}


int main(void){

	SDL_Event e;
	bool quit = false;
	int button_size = 50;//size of a button in pixels
	int num_buttons = 15; //number of buttons in one row/column
	int index; //index of a button
	int x;
	int y;

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
				x = e.button.x; //get coordinates of mouse click
				y = e.button.y;
				index = button_index(x, y, num_buttons, button_size); //get index
				//testing stuff				
				printf("%d\n", index);

				if (e.button.button == SDL_BUTTON_LEFT){ //left
					printf("clicked left at: %d, %d \n", x, y);
					//reveal(index, num_buttons)
					
				}
				if (e.button.button == SDL_BUTTON_RIGHT){//right
					printf("clicked right at: %d, %d \n", x, y);
					//if not revealed, toggle flag
					//else do nothing
				}
			}
		
		}
	
	}


	SDL_DestroyWindow(window);
	SDL_Quit();	
	
	return 0;

}
