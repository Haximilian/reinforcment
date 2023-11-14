#include <iostream>

#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect *object;
    bool continue_mainloop;
} mainloop_arguments_t;

void update_state(SDL_Rect *object, SDL_Keycode key)
{
    if (key == SDLK_a)
    {
        object->x -= 5;
    }
    if (key == SDLK_d)
    {
        object->x += 5;
    }
}

void mainloop(void *mainloop_arguments)
{
    mainloop_arguments_t *arguments = (mainloop_arguments_t *)mainloop_arguments;

    if (!arguments->continue_mainloop)
    {
        SDL_DestroyWindow(arguments->window);
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
            arguments->continue_mainloop = false;
        }
        if (event.type == SDL_KEYDOWN)
        {
            // std::cout << event.key.keysym.sym << std::endl;
            update_state(arguments->object, event.key.keysym.sym);
        }
    }

    // you can either clear the screen and re-draw other objects
    // or, you can clear and re-draw objects that were updated
    SDL_SetRenderDrawColor(
        arguments->renderer,
        0,
        0,
        0,
        SDL_ALPHA_OPAQUE);
    SDL_RenderClear(arguments->renderer);

    SDL_SetRenderDrawColor(arguments->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(arguments->renderer, arguments->object);
    SDL_RenderPresent(arguments->renderer);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);

    mainloop_arguments_t arguments;
    arguments.window = SDL_CreateWindow(
        "application",
        0,
        0,
        640,
        480,
        SDL_WINDOW_SHOWN);
    arguments.renderer = SDL_CreateRenderer(
        arguments.window,
        -1,
        SDL_RENDERER_ACCELERATED);

    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 20;
    rectangle.h = 20;
    arguments.object = &rectangle;

    arguments.continue_mainloop = true;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(mainloop, &arguments, 0, 1);
#else
    while (true)
    {
        mainloop(&arguments);
    }
#endif

    return 0;
}
