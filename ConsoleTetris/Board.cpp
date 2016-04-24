#include <cstdlib>
using std::srand;
using std::rand;
#include <ctime>
using std::time;

#include "Graphics.h"
#include "Board.h"
#include "Tile.h"

Board::Board() : m_level(0), m_lines(0), m_score(0), m_gameover(false)
{
	for (int i = 0; i < FIELD_SIZE; i++)
		m_field[i] = 0;
}

Board::~Board()
{
	if (m_tile != nullptr)
		delete m_tile;
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

void Board::ClrTile()
{
	int pos = 0;
	for (int i = 0; i < NUM_COORD; i += 2)
	{
		pos = m_tile->GetCoord(i) + (m_tile->GetCoord(i + 1) * ROW_LEN);
		m_field[pos] = 0;
	}
}

void Board::DrawTile()
{
	int pos = 0;
	for (int i = 0; i < NUM_COORD; i += 2)
	{
		pos = m_tile->GetCoord(i) + (m_tile->GetCoord(i + 1) * ROW_LEN);
		m_field[pos] = 0x88 | m_tile->GetCol();
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
			masked_tile = m_field[i - 2] & 0x88;
			if (masked_tile == 0x80 || (i - 1) % 10 == 0)
				collision |= COL_LL;
			masked_tile = m_field[i + 1] & 0x88;
			if (masked_tile == 0x80 || (i + 1) % 10 == 0)
				collision |= COL_R;
			masked_tile = m_field[i + 2] & 0x88;
			if (masked_tile == 0x80 || (i + 2) % 10 == 0)
				collision |= COL_RR;
			masked_tile = m_field[i + 10] & 0x88;
			if (masked_tile == 0x80 || (i + 10) > FIELD_SIZE)
				collision |= COL_B;
			masked_tile = m_field[i + 20] & 0x88;
			if (masked_tile == 0x80 || (i + 20) > FIELD_SIZE)
				collision |= COL_BB;
		}
	}

	return collision;
}

void Board::MoveTile(int dir)
{
	ClrTile();
	unsigned char collision = CheckCollision();

	/*unsigned char collision = CheckCollision() & COL_B;
	if (collision != COL_B)
	{
		unsigned char tile = m_field[coords[0] + (coords[1] * ROW_LEN)];
		ClrTile();

		int pos = 0;

		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = m_tile->GetCoord(i) + (m_tile->GetCoord(i + 1) * ROW_LEN);
			m_tile->GetCoord(i + 1) += 1;
			m_field[pos + ROW_LEN] = tile;
		}
	}
	else
	{
		int pos = 0;
		for (int i = 0; i < NUM_COORD; i += 2)
		{
			pos = m_tile->GetCoord(i) + (m_tile->GetCoord(i + 1) * ROW_LEN);
			m_field[pos] = m_field[pos] & 0xF0;
		}
		SpawnTet();
	}*/


	switch (dir)
	{
	case 0:
		if (collision & COL_B == 0)
			m_tile->Drop();
		else
		{
			DrawTile();
			SpawnTile();
		}
		break;
	case 1:
		if (collision & COL_L == 0)
			m_tile->MoveLeft();
		break;
	case 2:
		// TODO
		break;
	case 3:
		if (collision & COL_R == 0)
			m_tile->MoveRight();
		break;
	case 4:
		// Rotate Counter-Clockwise
		m_tile->RotLeft();
		break;
	case 5:
		// Rotate Clockwise
		m_tile->RotRight();
		break;
	default:
		break;
	}

	DrawTile();
}

void Board::SpawnTile()
{
	int randVal = 0;

	srand(time(0));

	randVal = rand() % 6;

	delete m_tile;
	m_tile = new Tile(randVal);
}