#include "CellularAutomatonScene.h"

const color_t white{ 255, 255, 255, 255 };
const color_t black{ 0, 0, 0, 255 };
const int rule = 22;

bool CellularAutomatonScene::Initialize()
{
	m_renderer.Initialize();
	m_renderer.CreateWindow("Cellular Automaton", 800, 600);

	m_input.Initialize();
	m_input.Update();

	m_framebuffer = std::make_unique<Framebuffer>(m_renderer, m_renderer.m_width / 2, m_renderer.m_height / 2);
	m_cells = std::make_unique<Cells<uint8_t>>(m_framebuffer->m_width, m_framebuffer->m_height);

	return true;
}

void CellularAutomatonScene::Update()
{
	Scene::Update();

	// middle column, top row, set it to 1 (true)
	m_cells->Write(m_cells->GetWidth() / 2, 0, 1);


	for (int y = 0; y < m_cells->GetHeight() - 1; y++)
	{
		for (int x = 1; x < m_cells->GetWidth() - 1; x++)
		{
			int i = 0;

			// creating a 3 bit sequence (0-7) based on what's in the surrounding cells
			i |= m_cells->Read(x, y) << 1;
			i |= m_cells->Read(x - 1, y) << 2;
			i |= m_cells->Read(x + 1, y);

			uint8_t state = (rule & 1 << i);
			m_cells->Write(x, y + 1, state);
		}
	}
}

void CellularAutomatonScene::Draw()
{
	m_framebuffer->Clear(color_t{ 0, 0, 0, 255 });

	// write cells to the frame buffer
	for (int i = 0; i < m_cells->GetData().size(); i++)
	{
		// draw the booleans in the cells on the screen as white = true and black = false
		m_framebuffer->m_buffer[i] = (m_cells->GetData()[i]) ? white : black;
	}


	/*
	for (int i = 0; i < 100000; i++)
	{
		m_framebuffer->DrawPoint(rand() % m_renderer.m_width / 2, rand() % m_renderer.m_height / 2, color_t{ uint8_t(rand() % 255), uint8_t(rand() % 255), uint8_t(rand() % 255), 255 });
	}
	*/


	// update framebuffer
	m_framebuffer->Update();

	// show screen
	m_renderer = *m_framebuffer;
	SDL_RenderPresent(m_renderer.m_renderer);
}
