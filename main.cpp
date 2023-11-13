
#include <iostream>

#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

static SDL_Window *window;
static bool gameIsRunning = true;

void mainloop(void)
{
    if (!gameIsRunning)
    {
        SDL_DestroyWindow(window);
        SDL_Delay(3000);
        SDL_Quit();

#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#else
        exit(0);
#endif
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gameIsRunning = false;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            std::cout << "mouse has been moved\n";
        }
        if (event.type == SDL_KEYDOWN)
        {
            std::cout << "a key has been pressed\n";
            if (event.key.keysym.sym == SDLK_0)
            {
                std::cout << "0 was pressed\n";
            }
            else
            {
                std::cout << "0 was not pressed\n";
            }
        }
    }
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("C++ SDL2 Window",
                              0,
                              2500,
                              640,
                              480,
                              SDL_WINDOW_SHOWN);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(mainloop, 0, 1);
#else
    while (1)
    {
        mainloop();
    }
#endif

    return 0;
}
