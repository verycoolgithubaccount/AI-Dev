#pragma once
#include "Scene.h"
#include "Framebuffer.h"
#include "Cells.h"
#include <memory>

class CellularAutomatonScene : public Scene
{
private:


public:
	bool Initialize() override;
	void Update() override;
	void Draw() override;

public:
	std::unique_ptr<Framebuffer> m_framebuffer;
	std::unique_ptr<Cells<bool>> m_cells;
};

