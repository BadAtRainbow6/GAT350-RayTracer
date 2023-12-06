#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    std::cout << "Hello World" << std::endl;

    Random rand;
    rand.seedRandom(static_cast<unsigned int>(time(nullptr)));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("RayTracer", 800, 600);

    Canvas canvas(800, 600, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);

    Scene scene = Scene(color3_t{ 1, 1, 1 }, color3_t{ 0, 0, 0 }); // sky color could be set with the top and bottom color
    scene.SetCamera(camera);

    // create material
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

    // create objects -> add to scene
    for (int i = 0; i < 10; i++) {
        auto sphere = std::make_unique<Sphere>(glm::vec3{ rand.random(glm::vec3{ -1, -1, -5 }, glm::vec3{ 1, 1, -8 }) }, rand.random(0.5f, 2.0f), material);
        scene.AddObject(std::move(sphere));
    }

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        SDL_PollEvent(&event);

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

        scene.Render(canvas);
        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();

    return 0;
}