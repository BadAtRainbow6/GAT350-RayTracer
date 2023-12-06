#include "Renderer.h"
#include "Random.h"
#include "Canvas.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include <memory>
#include <iostream>
#include <SDL.h>

using namespace std;

int main(int, char**)
{
	std::cout << "hello world!\n";
	seedRandom((uint32_t)time(nullptr));

	//<create renderer>
	Renderer renderer;
	//<initialize renderer>
	renderer.Initialize();
	renderer.CreateWindow("RayTracing", 1200, 800);
	Canvas canvas(1200, 800, renderer);

	float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 90.0f, aspectRatio);

	Scene scene(1); // sky color could be set with the top and bottom color
	scene.SetCamera(camera);

	// create material
	auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

	for (int i = 0; i < 10; i++) {
		// create objects -> add to scene
		auto sphere = std::make_unique<Sphere>(glm::vec3{ random(5,-5), random(5,-5), random(-5, -20) }, random(0.5f, 2), material);
		scene.AddObject(std::move(sphere));
	}

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		for (int i = 0; i < 1000; i++) canvas.DrawPoint({ random01() * canvas.GetSize().x, random01() * canvas.GetSize().y }, { random01(), random01(), random01(), 1 });

		canvas.Clear({ 0, 0, 0, 1 });
		scene.Render(canvas);
		canvas.Update();

		renderer.PresentCanvas(canvas);
	}

	//<shutdown renderer>
	renderer.Shutdown();

	return 0;
}