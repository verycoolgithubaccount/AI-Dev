#include "GOLScene.h"

const color_t white{ 255, 255, 255, 255 };
const color_t black{ 0, 0, 0, 255 };
const int rule = 22;

Cells<uint8_t>* currentCells;
Cells<uint8_t>* nextCells;

bool GOLScene::Initialize()
{
	m_renderer.Initialize();
	m_renderer.CreateWindow("Game of Life", 800, 600);

	m_input.Initialize();
	m_input.Update();

	m_framebuffer = std::make_unique<Framebuffer>(m_renderer, m_renderer.m_width / 5, m_renderer.m_height / 5);
	m_cellsA = std::make_unique<Cells<uint8_t>>(m_framebuffer->m_width, m_framebuffer->m_height);
	m_cellsB = std::make_unique<Cells<uint8_t>>(m_framebuffer->m_width, m_framebuffer->m_height);

	return true;
}

void GOLScene::Update()
{
	Scene::Update();
	m_frame++;

	currentCells = (m_frame % 2) ? m_cellsA.get() : m_cellsB.get();
	nextCells = (m_frame % 2) ? m_cellsB.get() : m_cellsA.get();

	std::fill(nextCells->GetData().begin(), nextCells->GetData().end(), 0);

	if (m_input.GetKeyDown(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < nextCells->GetData().size(); i++)
		{
			nextCells->GetData()[i] = (rand() % 100 == 0) ? 1 : 0;
		}
	}

	/*
	for (int y = 1; y < nextCells->GetHeight() - 1; y++)
	{
		for (int x = 1; x < nextCells->GetWidth() - 1; x++)
		{
			int count = 0;

			count += currentCells->Read(x - 1, y - 1);
			count += currentCells->Read(x + 0, y - 1);
			count += currentCells->Read(x + 1, y - 1);
			count += currentCells->Read(x - 1, y + 0);
			count += currentCells->Read(x + 1, y + 0);
			count += currentCells->Read(x - 1, y + 1);
			count += currentCells->Read(x + 0, y + 1);
			count += currentCells->Read(x + 1, y + 1);
	*/
	int height = nextCells->GetHeight();
	int width = nextCells->GetWidth();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int count = 0;
			count += currentCells->Read((x + width - 1) % width, (y + height - 1) % height);
			count += currentCells->Read((x + width + 0) % width, (y + height - 1) % height);
			count += currentCells->Read((x + width + 1) % width, (y + height - 1) % height);
			count += currentCells->Read((x + width - 1) % width, (y + height + 0) % height);
			count += currentCells->Read((x + width + 1) % width, (y + height + 0) % height);
			count += currentCells->Read((x + width - 1) % width, (y + height + 1) % height);
			count += currentCells->Read((x + width + 0) % width, (y + height + 1) % height);
			count += currentCells->Read((x + width + 1) % width, (y + height + 1) % height);
			// Game of life rules
			uint8_t currentState = currentCells->Read(x, y);
			if (currentState)
			{
				// Die unless you have 2 or 3 live neighbors
				if (count == 2 || count == 3) nextCells->Write(x, y, 1);
			}
			else
			{
				// Born if exactly 3 live neighbors
				if (count == 3) nextCells->Write(x, y, 1);
			}
		}
	}
}

void GOLScene::Draw()
{
	m_framebuffer->Clear(color_t{ 0, 0, 0, 255 });

	// write cells to the frame buffer
	for (int i = 0; i < nextCells->GetData().size(); i++)
	{
		// draw the booleans in the cells on the screen as white = true and black = false
		m_framebuffer->m_buffer[i] = (nextCells->GetData()[i]) ? white : black;
	}

	// update framebuffer
	m_framebuffer->Update();

	// show screen
	m_renderer = *m_framebuffer;
	SDL_RenderPresent(m_renderer.m_renderer);
}
