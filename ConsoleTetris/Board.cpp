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
	unsigned char collision = CheckCollision() & COL_B;
	if (collision != COL_B)
	{
		unsigned char tile = m_field[currCoords[0] + (currCoords[1] * ROW_LEN)];
		ClrTile();

		int pos = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			currCoords[i + 1] += 1;
			m_field[pos + ROW_LEN] = tile;
		}
	}
	else
	{
		int pos = 0;
		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			m_field[pos] = m_field[pos] & 0xF0;
		}
		SpawnTet();
	}
}

void Board::MoveLeft()
{
	unsigned char collision = CheckCollision() & COL_L;
	if (collision != COL_L)
	{
		unsigned char tile = m_field[currCoords[0] + (currCoords[1] * ROW_LEN)];
		ClrTile();

		int pos = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			currCoords[i] -= 1;
			m_field[pos - 1] = tile;
		}
	}
}

void Board::MoveRight()
{
	unsigned char collision = CheckCollision() & COL_R;
	if (collision != COL_R)
	{
		unsigned char tile = m_field[currCoords[0] + (currCoords[1] * ROW_LEN)];
		ClrTile();

		int pos = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			currCoords[i] += 1;
			m_field[pos + 1] = tile;
		}
	}
}

void Board::RotLeft()
{
	unsigned char tile = m_field[currCoords[0] + (currCoords[1] * ROW_LEN)];

	if (tile == 0x98 || tile == 0xE8 || tile == 0xF8)
	{
		
	}

	if (tile != 0xA8)
	{
		int tempArr[NUM_COORD];

		for (int i = 0; i < NUM_COORD; i++)
			tempArr[i] = currCoords[i];
		int pos = 0;

		ClrTile();

		int midX = currCoords[2];
		int midY = currCoords[3];
		int temp = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			currCoords[i] -= midX;
			currCoords[i + 1] -= midY;

			temp = currCoords[i];
			currCoords[i] = currCoords[i + 1];
			currCoords[i + 1] = temp * -1;

			currCoords[i] += midX;
			currCoords[i + 1] += midY;

			if ((currCoords[i] < 0) || (currCoords[i] > 9) || (currCoords[i + 1] > FIELD_SIZE / ROW_LEN))
			{
				for (int i = 0; i < NUM_COORD; i++)
					currCoords[i] = tempArr[i];
				i = NUM_COORD;
			}
		}

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			m_field[pos] = tile;
		}
	}
}

void Board::RotRight()
{
	unsigned char tile = m_field[currCoords[0] + (currCoords[1] * ROW_LEN)];
	
	if (tile == 0x98 || tile == 0xE8 || tile == 0xF8)
	{
		
	}
	
	if (tile != 0xA8)
	{
		int tempArr[NUM_COORD];

		for (int i = 0; i < NUM_COORD; i++)
			tempArr[i] = currCoords[i];
		int pos = 0;

		ClrTile();

		int midX = currCoords[2];
		int midY = currCoords[3];
		int temp = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			currCoords[i] -= midX;
			currCoords[i + 1] -= midY;

			temp = currCoords[i];
			currCoords[i] = currCoords[i + 1] * -1;
			currCoords[i + 1] = temp;

			currCoords[i] += midX;
			currCoords[i + 1] += midY;

			if ((currCoords[i] < 0) || (currCoords[i] > 9) || (currCoords[i + 1] > FIELD_SIZE / ROW_LEN))
			{
				for (int i = 0; i < NUM_COORD; i++)
					currCoords[i] = tempArr[i];
				i = NUM_COORD;
			}
		}

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
			m_field[pos] = tile;
		}
	}
}

void Board::ClrTile()
{
	int pos = 0;
	for (int i = 0; i < NUM_COORD; i += 2)
	{
		pos = currCoords[i] + (currCoords[i + 1] * ROW_LEN);
		m_field[pos] = 0;
	}
}

unsigned char Board::CheckCollision()
{
	unsigned char collision = 0;

	int pos = 0;
	unsigned char masked_tile = 0;

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		masked_tile = m_field[i] & 0x0F;
		if (masked_tile == 0x08)
		{
			masked_tile = m_field[i - 1] & 0x88;
			if (masked_tile == 0x80 || (i) % 10 == 0)
				collision |= COL_L;
			masked_tile = m_field[i + 1] & 0x88;
			if (masked_tile == 0x80 || (i + 1) % 10 == 0)
				collision |= COL_R;
			masked_tile = m_field[i + 10] & 0x88;
			if (masked_tile == 0x80 || (i + 10) > FIELD_SIZE)
				collision |= COL_B;
		}
	}

	return collision;
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
	int randVal = 0;

	srand(time(0));

	randVal = rand() % 6;

	switch (randVal)
	{
	case 0:			// I
		/*
		*	X
		*	C
		*	X
		*	X
		*/
		currCoords[0] = 0;
		currCoords[1] = -1;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 0;
		currCoords[5] = 1;
		currCoords[6] = 0;
		currCoords[7] = 2;
		break;
	case 1:			// O
		currCoords[0] = 0;
		currCoords[1] = 0;
		currCoords[2] = 0;
		currCoords[3] = 1;
		currCoords[4] = 1;
		currCoords[5] = 0;
		currCoords[6] = 1;
		currCoords[7] = 1;
		break;
	case 2:			// T
		/*
		*	XCX
		*	 X
		*/
		currCoords[0] = -1;
		currCoords[1] = 0;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 1;
		currCoords[5] = 0;
		currCoords[6] = 0;
		currCoords[7] = 1;
		break;
	case 3:			// L
		/*
		*	X
		*	C
		*	XX
		*/
		currCoords[0] = 0;
		currCoords[1] = -1;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 0;
		currCoords[5] = 1;
		currCoords[6] = 1;
		currCoords[7] = 1;
		break;
	case 4:			// J
		/*
		*	 X
		*	 C
		*	XX
		*/
		currCoords[0] = 0;
		currCoords[1] = -1;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 0;
		currCoords[5] = 1;
		currCoords[6] = -1;
		currCoords[7] = 1;
		break;
	case 5:			// S
		/*
		*	 CX
		*	XX
		*/
		currCoords[0] = 1;
		currCoords[1] = 0;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 0;
		currCoords[5] = 1;
		currCoords[6] = -1;
		currCoords[7] = 1;
		break;
	case 6:			// Z
		/*
		*	XC
		*	 XX
		*/
		currCoords[0] = -1;
		currCoords[1] = 0;
		currCoords[2] = 0;
		currCoords[3] = 0;
		currCoords[4] = 0;
		currCoords[5] = 1;
		currCoords[6] = 1;
		currCoords[7] = 1;
		break;
	default:
		cout << "Error! Invalid value!" << endl;
		break;
	}

	AddToBoard(static_cast<unsigned char>(randVal + 1) << 4);
}

void Board::AddToBoard(unsigned char col)
{
	int pos = 0;
	for (int i = 0; i < NUM_COORD; i += 2)
	{
		currCoords[i] = currCoords[i] + 5;
		pos = currCoords[i] + currCoords[i + 1] * ROW_LEN;
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