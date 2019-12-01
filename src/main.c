#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define IMAGE_PATH "resources/pikachu.png"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Texture *load_texture(const char *file, SDL_Renderer *ren) {
  SDL_Texture *texture = IMG_LoadTexture(ren, file);
  return texture;
}

void render_texture(SDL_Texture *texture,
                    SDL_Renderer *ren,
                    int x, int y,
                    int w, int h)
{
  // Setup the destination rectancle
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  dst.w = w;
  dst.h = h;

  // Query the texture
  SDL_RenderCopy(ren, texture, NULL, &dst);
}

// We're not cleaning resource within main function
// OS will clean them anyway
int main()
{
  // SDL initialization
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER)) {
    return 1;
  }

  // SDL_image initialization
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("My Program",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     SCREEN_WIDTH,
                                     SCREEN_HEIGHT,
                                     SDL_WINDOW_SHOWN);
  if (!win) {
    return 1;
  }

  // NOTE: `SDL_RENDERER_PRESENTVSYNC` flag limits FPS to 60 frames per second
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED
                                                | SDL_RENDERER_PRESENTVSYNC);
  if (!ren) {
    return 1;
  }

  // LOAD RESOURCE
  SDL_Texture *image = load_texture(IMAGE_PATH, ren);
  if (!image) {
    return 1;
  }

  // LOOP
  bool running = true;

  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {

      // Exit program
      case SDL_QUIT:
        {
          running = false;
        } break;
      }
    }

    // Clear the renderer
    SDL_RenderClear(ren);
    render_texture(image, ren, 100, 100, 300, 300);

    // Update the screen
    SDL_RenderPresent(ren);
  }


  printf("Exiting gracefully. See you!\n");
  return 0;
}
