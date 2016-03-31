#include <conio.h>

#include "Graphics.h"
#include "Board.h"

void ParseInput(Board & b, char in);

int main()
{
	Board b;
	long int clock = 0;

	b.SpawnTet();
	b.DrawBoard();
	b.DrawField();
	
	while (!b.GetGO()) // And bingo was his name-o!
	{
		if (_kbhit() != 0)
			ParseInput(b, _getch());

		if (clock == 5000)
		{
			b.DropTile();
			b.DrawBoard();
			b.DrawField();
			clock = 0;
		}
		clock++;
	}

	return 0;
}

void ParseInput(Board & b, char in)
{
	if (in == 'a')
		b.MoveTile(1);
	else if (in == 's')
		b.MoveTile(2);
	else if (in == 'd')
		b.MoveTile(3);
	else if (in == '[')
		b.MoveTile(4);
	else if (in == ']')
		b.MoveTile(5);

	b.DrawField();
}