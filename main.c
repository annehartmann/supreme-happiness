#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <time.h>

int button_size;
int num_buttons;
bool dead;


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
			dead = true;

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
	return;
	

}

int bomben_verteilen (int size, int array[], int anzahl_bomben){
	if (anzahl_bomben > size) {
		perror("Zu viele Bomben!!!");
		return 1;
	}
	time_t t;
	srand((unsigned) time(&t));
	for( int i = 0; i < anzahl_bomben; i++){
		int feld_index = rand() % size;
		if (array[feld_index] == -1) {
			i--;
		} else {
			//printf("%d \n", feld_index);
			array[feld_index] = -1;
		}
	}
	return 0;
}

int minenherum(int current_x, int current_y, int size, int array[]) {
	int counter = 0;
	for(int x_offset = -1; x_offset <= 1; ++x_offset){
		for(int y_offset = -1; y_offset <= 1; ++y_offset){
			int x_feld = current_x + x_offset;
			int y_feld = current_y + y_offset;
			int index = x_feld + y_feld * size;
		
			if(x_feld >= 0 && x_feld < size && y_feld >= 0 && y_feld < size){
				if(array[index] == -1){
					counter++;			
				}
			}
		}
	}
	return counter;
}

void update_zahlen(int size, int array[]) {
	for(int x = 0; x < size; x++) {
		for(int y = 0; y < size; y++) {
			int index = x + y * size;
			if (array[index] != -1) {
				array[index] = minenherum(x, y, size, array);
			}
		}
	}
}


void graph(int revealed[], int array[], int num_of_buttons,SDL_Window *window, int window_size,SDL_Renderer *renderer)
{	
	int all_buttons = num_of_buttons*num_of_buttons;
    	int num_lines = num_of_buttons - 1;
    	float len_lines = window_size/num_of_buttons;
	
	
	SDL_Texture *img0 = NULL;
	SDL_Texture *img1 = NULL;
	SDL_Texture *img2 = NULL;
	SDL_Texture *img3 = NULL;
	SDL_Texture *img4 = NULL;
	SDL_Texture *img5 = NULL;
	SDL_Texture *img6 = NULL;
	SDL_Texture *img7 = NULL;
	SDL_Texture *img8 = NULL;
	SDL_Texture *imgb = NULL;
		
		
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_Texture *images[9] = {img0,img1,img2,img3,img4,img5,img6,img7,img8};
	char path[100];
	for(int i = 0; i < 9; ++i) {
		snprintf(path, sizeof(path), "./%d.png", i);
		images[i] = IMG_LoadTexture(renderer, path);
		if (!images[i]) {
			fprintf(stderr, "IMG_LoadTexture: %s: %s\n", path, SDL_GetError());
		}
	}

	imgb = IMG_LoadTexture(renderer, "9.png");
	if (!imgb) {
		fprintf(stderr, "IMG_LoadTexture: imgb: %s\n", SDL_GetError());
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	if(SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) < 0){
		printf("SetRenderDrawColor: %s\n", SDL_GetError());
	}
	for (int i = 1; i <= num_lines; i += 1){
		SDL_Point p_x[2] = {{len_lines*i,0},{len_lines*i,window_size}};
		SDL_Point p_y[2] = {{0,len_lines*i},{window_size,len_lines*i}};
		SDL_RenderDrawLines(renderer, p_x, 2);
		SDL_RenderDrawLines(renderer, p_y, 2);
	}
	for (int i = 0; i < all_buttons; i++){
		int y_shift = i/num_of_buttons;
		int x_shift = i % num_of_buttons;
		SDL_Rect texr = {
			.x = len_lines * x_shift,
			.y = len_lines * y_shift,
			.w = len_lines,
			.h = len_lines
		};
		if(revealed[i] == 1){
			printf("Drawing x: %d, y: %d of type %d\n", x_shift, y_shift, array[i]);
			if(array[i] >= 0){
				printf("Drawing image %d\n", array[i]);
				SDL_RenderCopy(renderer, images[array[i]], NULL, &texr);
			}
			if(array[i] < 0){
				SDL_RenderCopy(renderer, imgb, NULL, &texr);
			}
		}
			   
		
	}
	SDL_RenderPresent(renderer);

    
}


int main(void){

	bool dead = false;
	SDL_Event e;
	bool quit = false;
	int button_size = 50;//size of a button in pixels
	int num_of_buttons = 5; //number of buttons in one row/column
	int index; //index of a button
	int x;
	int y;
	const int window_size = num_of_buttons * button_size;
	int array[25] = {0};
	int num_mines = 3;
	int dummy[25] = {-1,1,0,1,1,1,1,1,2,-1,1,1,2,-1,2,1,-1,2,1,1,1,1,1,0,0};
	int r[num_of_buttons * num_of_buttons];
	int all_buttons = num_of_buttons*num_of_buttons;
	for(int i = 0; i <= all_buttons; i++){
		r[i] = 0;
	}
	bomben_verteilen(num_of_buttons * num_of_buttons, array, num_mines);
	update_zahlen(num_buttons, array);
	SDL_Window *window; //create a window
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(
		"minesweeper",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(button_size * num_of_buttons),
		(button_size * num_of_buttons),
		SDL_WINDOW_ALWAYS_ON_TOP
	);
	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
			fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
		}
	if (window == NULL){ //prints error and quits program if window creation fails
		printf("could not create window: %s\n", SDL_GetError());
		return 1;
	}
	graph(r,dummy,num_of_buttons,window,window_size, renderer);
	while (!quit){ //listen for events until user quits program by closing window

		while(SDL_PollEvent(&e)){ //handle events
			if (e.type == SDL_QUIT){//close window if "x" is pressed
				quit = true;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN){ //listen for mouse clicks
				x = e.button.x; //get coordinates of mouse click
				y = e.button.y;
				index = button_index(x, y, num_of_buttons, button_size); //get index
						

				if (e.button.button == SDL_BUTTON_LEFT){ //left
					//printf("clicked left at: %d, %d \n", x, y);
					printf("clicked button %d\n", index);
					reveal(index, num_of_buttons, dummy, r);
					graph(r,dummy,num_of_buttons,window,window_size,renderer);
					
				}
				if (e.button.button == SDL_BUTTON_RIGHT){//right
					printf("clicked right at: %d, %d \n", x, y);
					//if not revealed, toggle flag
					//else do nothing
				}
			}
		
		}
	
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();	
	
	return 0;

}
