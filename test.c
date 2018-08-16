#include <SDL2/SDL.h>

/* Moving Rectangle */
int main(int argc, char *argv[])
{
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *texture;
        SDL_Event event;
	int number_of_buttons = atoi(argv[1]);
        SDL_Rect r[number_of_buttons];
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
                return 3;
        }

        window = SDL_CreateWindow("SDL_CreateTexture",
                        SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOWPOS_UNDEFINED,
                        1024, 768,
                        SDL_WINDOW_RESIZABLE);


        renderer = SDL_CreateRenderer(window, -1, 0);

        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
        for (int counter = 0; counter <= number_of_buttons; counter++) {
                SDL_PollEvent(&event);
                if(event.type == SDL_QUIT)
                        break;
		r[counter].x = 0 + counter*10;
		r[counter].y = 0 + counter*10;
		r[counter].w = 50;
		r[counter].h = 50;
	}
        SDL_SetRenderTarget(renderer, texture);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderDrawRects(renderer,r,number_of_buttons);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
        SDL_RenderFillRects(renderer, r, number_of_buttons);
        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
}
