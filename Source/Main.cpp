#include "ExampleScene.h"
#include "GOLScene.h"
#include "CellularAutomatonScene.h"
#include <memory>
#include <SDL.h>

int main(int, char**)
{
	std::unique_ptr<CellularAutomatonScene> scene = std::make_unique<CellularAutomatonScene>();

	scene->Initialize();
	while (!scene->IsQuit())
	{
		scene->Update();
		scene->Draw();
	}

	return 0;
}