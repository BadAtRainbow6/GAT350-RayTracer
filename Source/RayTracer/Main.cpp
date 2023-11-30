#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello World" << std::endl;

    Random rand;
    rand.seedRandom(static_cast<unsigned int>(time(nullptr)));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 400, 400);

    Canvas canvas(400, 300, renderer);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);

        renderer.PresentCanvas(canvas);

        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;
            }
            break;
        }

        canvas.Clear({ 0, 0, 0, 1 });
        for (int i = 0; i < 1000; i++) canvas.DrawPoint({ rand.random(0, 400), rand.random(0, 300) }, { rand.random01(), rand.random01(), rand.random01(), 1 });
        canvas.Update();
    }

    renderer.Shutdown();

    return 0;
}