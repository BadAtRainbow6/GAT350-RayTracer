#include "Renderer.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hello World" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 400, 400);

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }

    renderer.Shutdown();

    return 0;
}