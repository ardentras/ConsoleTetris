#include <iostream>
using std::cout;
using std::endl;
#include <Windows.h>

#pragma once
class Graphics
{
private:
	COORD m_cursor;
	HANDLE m_hStdout;
public:
	Graphics();
	~Graphics();

	void SetPos(int x, int y);
	void SetColor(char c);
};

