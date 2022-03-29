#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(0, 0, 0, &window, &renderer) < 0)
        exit(2);
   
    /* Main render loop */
    Uint8 done = 0;
    SDL_Event event;
    while (!done) {
        /* Check for events */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN ||
                event.type == SDL_FINGERDOWN) {
                done = 1;
            }
        }
        /* Draw a gray background */
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer);
        
        //Render red filled quad
        SDL_Rect fillRect = { 20, 20, 100, 300 };// SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );        
        SDL_RenderFillRect( renderer, &fillRect );

        /* Update the screen! */
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    exit(0);
}