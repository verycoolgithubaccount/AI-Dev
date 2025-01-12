#pragma once
#include <vector>

template<typename T>
class Cells
{
private:
	int m_width{ 0 };
	int m_height{ 0 };

	std::vector<T> m_data;

public:
	Cells(int width, int height) : 
		m_width{ width }, 
		m_height{ height } 
	{
		m_data.resize(width * height);
	}

	T Read(int x, int y) const { return m_data[x + (y * m_width)]; }
	void Write(int x, int y, const T& value) { m_data[x + (y * m_width)] = value; }

	std::vector<T>& GetData() { return m_data; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	void SetWidth(int w) { m_width = w; }
	void SetHeight(int h) { m_height = h; }

};