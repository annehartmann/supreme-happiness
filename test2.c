#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



#define IMG_PATH "./800px_COLOURBOX5397366.png"
#define IMG_PATH1 "./eins-im-kreis-1c-3062.svg.png"

/*static SDL_Point points[POINTS_COUNT] = {
    {0, 100},
    {640, 100},
    {0,200},
    {640,200}
};*/



int main(int argc, char* argv[])
{	
	int reveal[4] = {1,1,0,1};
	int type[4] = {0,1,0,1};
    const int window_size = 640;
    int num_buttons = 2;
	int all_buttons = num_buttons*num_buttons;
    int num_lines = num_buttons - 1;
    float len_lines = window_size/num_buttons;
	int r[num_buttons];
	int r_type[num_buttons];
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
		SDL_Texture *img0 = NULL;
		SDL_Texture *img1 = NULL;
        if (SDL_CreateWindowAndRenderer(window_size, window_size, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
				img0 = IMG_LoadTexture(renderer, IMG_PATH);
				img1 = IMG_LoadTexture(renderer, IMG_PATH1);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				for (int i = 1; i <= num_lines; i += 1){
					
					SDL_Point p_x[2] = {{len_lines*i,0},{len_lines*i,window_size}};
					SDL_Point p_y[2] = {{0,len_lines*i},{window_size,len_lines*i}};
					SDL_RenderDrawLines(renderer, p_x, 2);
					SDL_RenderDrawLines(renderer, p_y, 2);
				}
				for (int i = 0; i < all_buttons; i++){
					int y_shift = i/num_buttons;
					int x_shift = i % num_buttons;
					SDL_Rect texr; texr.x = len_lines*x_shift; texr.y = len_lines*y_shift; texr.w = len_lines; texr.h = len_lines;
					if(reveal[i] == 1){
						
						if(type[i] == 0){
							SDL_RenderCopy(renderer, img0, NULL, &texr);
						}
						if(type[i] == 1){
							SDL_RenderCopy(renderer, img0, NULL, &texr);
						}
					}		
				SDL_RenderPresent(renderer);	   
					
				}
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
    return 0;
}

