#include "ExampleScene.h"

bool ExampleScene::Initialize()
{
	m_renderer.Initialize();
	m_renderer.CreateWindow("Example", 800, 600);

	m_input.Initialize();
	m_input.Update();

	m_framebuffer = std::make_unique<Framebuffer>(m_renderer, m_renderer.m_width / 2, m_renderer.m_height / 2);

	return true;
}

void ExampleScene::Draw()
{
	m_framebuffer->Clear(color_t{ 0, 0, 0, 255 });

	for (int i = 0; i < 100000; i++)
	{
		m_framebuffer->DrawPoint(rand() % m_renderer.m_width / 2, rand() % m_renderer.m_height / 2, color_t{uint8_t (rand() % 255), uint8_t (rand() % 255), uint8_t (rand() % 255), 255});
	}
	

	// update framebuffer
	m_framebuffer->Update();

	// show screen
	m_renderer = *m_framebuffer;
	SDL_RenderPresent(m_renderer.m_renderer);
}
