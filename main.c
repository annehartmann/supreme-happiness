#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

int button_size;
int num_buttons;
bool dead;//log whether player died



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

void reveal(int button_index, int num_of_buttons, int array[], int revealed[]){
	//reveals number/mine of field button_index

	int number = array[button_index];//look up number in array
	if (revealed[button_index] == 1){//check that field is not already revealed
		return;
	}
	if (dead){
		printf("you're dead.\n");
		return;
	}
	revealed[button_index] = 1;//mark as revealed

	//booleans noting which neighbors the field has
	bool no_upper = true;
	bool no_lower = true;
	bool no_right = true;
	bool no_left = true;
	
	switch(number){
		case -1:
			//BOOM
			printf("BOOM!\n you died.\n");
			dead = true;//set player dead

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
			printf("revealed %d\n", number);
			break;
		case 0:
			//reveal empty field
			printf("revealed empty\n");
			//recursively call reveal on neighbors
			if ((button_index% num_of_buttons) != 0){
				//field has left neighbor
				reveal(button_index - 1, button_index, array, revealed);
				no_left = false;
			} 
			if ((button_index%num_of_buttons) != (num_of_buttons - 1)){
				//field has right neighbor
				reveal(button_index + 1, num_of_buttons, array, revealed);
				no_right = false;
			}
			if (button_index >= num_of_buttons){
				//field has upper neighbor
				reveal(button_index - num_of_buttons, num_of_buttons, array, revealed);
				no_upper = false;
			}
			if (button_index < (num_of_buttons * (num_of_buttons - 1))){
				//field has lower neighbor
				reveal(button_index + num_of_buttons, num_of_buttons, array, revealed);
				no_lower = false;
			}
			if (!no_left && !no_upper){
				//field has upper left neighbor
				reveal(button_index - (num_of_buttons + 1), num_of_buttons, array, revealed);
			}
			if (!no_upper && !no_right){
				//field has upper right neighbor
				reveal(button_index - num_of_buttons + 1, num_of_buttons, array, revealed);
			}
			if (!no_left && !no_lower){
				//field has lower left neighbor
				reveal(button_index + (num_of_buttons - 1), num_of_buttons, array, revealed);
			}
			if (!no_lower && !no_right){
				//field has lower right neighbor
				reveal(button_index + num_of_buttons + 1, num_of_buttons, array, revealed);
			}
			break;

		default:
			perror("This should not happen. Complain to Anne.");
	}

	//check whether player has won
	return;
	

}


int main(void){

	bool dead = false;//set player alive
	SDL_Event e;
	bool quit = false;
	int button_size = 50;//size of a button in pixels
	int num_buttons = 5; //number of buttons in one row/column
	int index; //index of a button
	int x;
	int y;
	int dummy[25] = {-1,1,0,1,1,1,1,1,2,-1,1,1,2,-1,2,1,-1,2,1,1,1,1,1,0,0};
	int r[num_buttons * num_buttons];

	SDL_Window *window; //create a window
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(button_size * num_buttons),
		(button_size * num_buttons),
		SDL_WINDOW_ALWAYS_ON_TOP
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
						

				if (e.button.button == SDL_BUTTON_LEFT){ //left
					//printf("clicked left at: %d, %d \n", x, y);
					printf("clicked button %d\n", index);
					reveal(index, num_buttons, dummy, r);
					
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
