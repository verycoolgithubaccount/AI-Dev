#pragma once
#include "Scene.h"
#include "Framebuffer.h"
#include "Cells.h"
#include <memory>

class GOLScene : public Scene
{
private:
	int m_frame{ 0 };

public:
	bool Initialize() override;
	void Update() override;
	void Draw() override;

	int GetFrame() { return m_frame; }

public:
	std::unique_ptr<Framebuffer> m_framebuffer;
	std::unique_ptr<Cells<uint8_t>> m_cellsA;
	std::unique_ptr<Cells<uint8_t>> m_cellsB;

};

