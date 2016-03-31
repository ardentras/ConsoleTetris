#include <cstdlib>
using std::srand;
using std::rand;
#include <ctime>
using std::time;

#include "Graphics.h"
#include "Board.h"

Board::Board() : m_level(0), m_lines(0), m_score(0), m_gameover(false)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		m_field[i] = 0;
}

Board::~Board()
{
}

void Board::DrawField()
{
	unsigned char color = 0;

	for (int i = 20; i < FIELD_SIZE; i++)
	{
		if (m_field[i] > 0)
			// Shifts bits into foreground color, ORs 1 to beginning
			// so intensity is always high.
			color = ((m_field[i] >> 4) & 0x0F) | 0x08;
		else
			color = 0x00;

		g.SetColor(color);
		g.SetPos(i % ROW_LEN + 15, i / ROW_LEN);
		cout << (char)219;
	}

	g.SetColor(0x0F);
}

void Board::DrawBoard()
{
	g.SetPos(3, 1);

	cout << (char)201 << (char)185;
	cout << "NEXT";
	cout << (char)204 << (char)187;

	for (int i = 0; i < 4; i++)
	{
		g.SetPos(3, 2 + i);
		cout << (char)186;
		g.SetPos(10, 2 + i);
		cout << (char)186;
	}

	g.SetPos(3, 6);

	cout << (char)200;
	for (int i = 0; i < 6; i++)
		cout << (char)205;
	cout << (char)188;

	g.SetPos(0, 8);

	cout << " Level: " << m_level << "\n"
		<< " Lines: " << m_lines << "\n\n"
		<< " Score: " << m_score << "\n";

	g.SetPos(14, 1);

	for (int i = 0; i < 12; i++)
		cout << (char)219;

	for (int i = 0; i < 20; i++)
	{
		g.SetPos(14, 2 + i);
		cout << (char)219;
		g.SetPos(25, 2 + i);
		cout << (char)219;
	}

	g.SetPos(14, 22);

	for (int i = 0; i < 12; i++)
		cout << (char)219;
}

void Board::DropTile()
{
	unsigned char masked_tile = 0;
	int collision_pt = 0;
	bool spawn_next = false;

	for (int i = FIELD_SIZE - 1; i >= 0; i--)
	{
		masked_tile = m_field[i] & 0x0F;
		if (masked_tile == 0x08)
		{
			if (spawn_next)
			{
				m_field[i] -= 8;
				if (i > collision_pt)
				{
					m_field[i - ROW_LEN] = m_field[i];
					m_field[i] = 0;
				}
				if (i < ROW_LEN * 2)
					m_gameover = true;
			}
			else if (i < FIELD_SIZE - ROW_LEN && m_field[i + ROW_LEN] == 0)
			{
				m_field[i + ROW_LEN] = m_field[i];
				m_field[i] = 0;
			}
			else
			{
				m_field[i] -= 8;
				collision_pt = i;
				i = FIELD_SIZE - 1;
				spawn_next = true;
			}
		}
	}

	if (spawn_next)
		SpawnTet();
}

void Board::MoveLeft()
{
	unsigned char masked_tile = 0;
	int count = 0;
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		masked_tile = m_field[i] & 0x0F;
		if (masked_tile == 0x08 && m_field[i - 1] == 0 && i % 10 != 0)
		{
			m_field[i - 1] = m_field[i];
			m_field[i] = 0;
			count++;
		}
		else if (masked_tile == 0x08)
		{
			while (count > 0)
			{
				i--;
				masked_tile = m_field[i] & 0x0F;
				if (masked_tile == 0x08)
				{
					m_field[i + 1] = m_field[i];
					m_field[i] = 0;
					count--;
				}
			}
			i = FIELD_SIZE;
		}
	}
}

void Board::MoveRight()
{
	unsigned char masked_tile = 0;
	int count = 0;
	for (int i = FIELD_SIZE - 1; i >= 0; i--)
	{
		masked_tile = m_field[i] & 0x0F;
		if (masked_tile == 0x08 && m_field[i + 1] == 0 && (i - 9) % 10 != 0)
		{
			m_field[i + 1] = m_field[i];
			m_field[i] = 0;
			count++;
		}
		else if (masked_tile == 0x08)
		{
			while (count > 0)
			{
				i++;
				masked_tile = m_field[i] & 0x0F;
				if (masked_tile == 0x08)
				{
					m_field[i - 1] = m_field[i];
					m_field[i] = 0;
					count--;
				}
			}
			i = -1;
		}
	}
}

void Board::RotLeft()
{
}

void Board::RotRight()
{
}

void Board::MoveTile(int dir)
{
	switch (dir)
	{
	case 1:
		MoveLeft();
		break;
	case 2:
		// TODO
		break;
	case 3:
		MoveRight();
		break;
	case 4:
		// Rotate Counter-Clockwise
		RotLeft();
		break;
	case 5:
		// Rotate Clockwise
		RotRight();
		break;
	default:
		break;
	}
}

void Board::SpawnTet()
{
	int grid[8];
	int randVal = 0;

	srand(time(0));

	randVal = rand() % 6;

	switch (randVal)
	{
	case 0:			// I
		grid[0] = 0;
		grid[1] = 0;
		grid[2] = 0;
		grid[3] = 1;
		grid[4] = 0;
		grid[5] = 2;
		grid[6] = 0;
		grid[7] = 3;
		break;
	case 1:			// O
		grid[0] = 0;
		grid[1] = 0;
		grid[2] = 0;
		grid[3] = 1;
		grid[4] = 1;
		grid[5] = 0;
		grid[6] = 1;
		grid[7] = 1;
		break;
	case 2:			// T
		grid[0] = 1;
		grid[1] = 0;
		grid[2] = 0;
		grid[3] = 1;
		grid[4] = 1;
		grid[5] = 1;
		grid[6] = 2;
		grid[7] = 1;
		break;
	case 3:			// L
		grid[0] = 0;
		grid[1] = 0;
		grid[2] = 0;
		grid[3] = 1;
		grid[4] = 0;
		grid[5] = 2;
		grid[6] = 1;
		grid[7] = 2;
		break;
	case 4:			// J
		grid[0] = 1;
		grid[1] = 0;
		grid[2] = 1;
		grid[3] = 1;
		grid[4] = 0;
		grid[5] = 2;
		grid[6] = 1;
		grid[7] = 2;
		break;
	case 5:			// S
		grid[0] = 1;
		grid[1] = 0;
		grid[2] = 2;
		grid[3] = 0;
		grid[4] = 0;
		grid[5] = 1;
		grid[6] = 1;
		grid[7] = 1;
		break;
	case 6:			// Z
		grid[0] = 0;
		grid[1] = 0;
		grid[2] = 1;
		grid[3] = 0;
		grid[4] = 1;
		grid[5] = 1;
		grid[6] = 2;
		grid[7] = 1;
		break;
	default:
		cout << "Error! Invalid value!" << endl;
		break;
	}

	AddToBoard(grid, static_cast<unsigned char>(randVal + 1) << 4);
}

void Board::AddToBoard(int grid[], unsigned char col)
{
	int pos = 0;
	for (int i = 0; i < 8; i += 2)
	{
		pos = grid[i] + 4 + (grid[i + 1] * ROW_LEN);
		m_field[pos] = 0x88 | col;
	}
}

bool Board::GetGO()
{
	return m_gameover;
}

void Board::SetGO(bool go)
{
	m_gameover = go;
}