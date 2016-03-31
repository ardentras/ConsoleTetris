#include "Graphics.h"

Graphics::Graphics() : m_hStdout(GetStdHandle(STD_OUTPUT_HANDLE))
{
	SetConsoleTitle(TEXT("Tetris!"));
}

Graphics::~Graphics()
{
}

void Graphics::SetPos(int x, int y)
{
	m_cursor.X = x;
	m_cursor.Y = y;

	SetConsoleCursorPosition(m_hStdout, m_cursor);
}

void Graphics::SetColor(char c)
{
	// This parses color as bg, then fg with bits in order of iRGB
	SetConsoleTextAttribute(m_hStdout, c);
}