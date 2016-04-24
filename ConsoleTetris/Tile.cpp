#include "Tile.h"

Tile::Tile(int type)
{
	switch (type)
	{
	case 0:			// I
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = I_TILE[i];
		break;
	case 1:			// O
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = O_TILE[i];
		break;
	case 2:			// T
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = T_TILE[i];
		break;
	case 3:			// L
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = L_TILE[i];
		break;
	case 4:			// J
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = J_TILE[i];
		break;
	case 5:			// S
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = S_TILE[i];
		break;
	case 6:			// Z
		for (int i = 0; i < NUM_COORD; i++)
			m_coords[i] = Z_TILE[i];
		break;
	default:
		break;
	}

	m_col = static_cast<unsigned char>(type + 1) << 4;
	for (int i = 0; i < NUM_COORD / 4; i += 2)
		m_curr[i] = m_coords[i] + 5;
}

Tile::~Tile()
{
}

void Tile::Drop()
{
	int midY = m_curr[3];

	for (int i = 0; i < NUM_COORD; i += 2)
	{
		m_curr[i + 1] -= midY;
		m_curr[i + 1] -= 1;
		m_curr[i + 1] += midY;
	}
}

void Tile::MoveLeft()
{
	int midX = m_curr[2];

	for (int i = 0; i < NUM_COORD; i += 2)
	{
		m_curr[i] -= midX;
		m_curr[i] -= 1;
		m_curr[i] += midX;
	}
}

void Tile::MoveRight()
{
	int midX = m_curr[2];

	for (int i = 0; i < NUM_COORD; i += 2)
	{
		m_curr[i] -= midX;
		m_curr[i] += 1;
		m_curr[i] += midX;
	}
}

void Tile::RotLeft()
{
	m_rot--;
	if (m_rot == 0)
		m_rot = 4;

	int midX = m_curr[2];
	int midY = m_curr[3];

	for (int i = 0; i < NUM_COORD / 4; i += 2)
	{
		m_curr[i] -= midX;
		m_curr[i + 1] -= midY;

		m_curr[i] = m_coords[i * m_rot];
		m_curr[i + 1] = m_coords[(i + 1) * m_rot];

		m_curr[i] += midX;
		m_curr[i + 1] += midY;
	}
}

void Tile::RotRight()
{
	m_rot++;
	if (m_rot == 5)
		m_rot = 1;

	int midX = m_curr[2];
	int midY = m_curr[3];

	for (int i = 0; i < NUM_COORD / 4; i += 2)
	{
		m_curr[i] -= midX;
		m_curr[i + 1] -= midY;

		m_curr[i] = m_coords[i * m_rot];
		m_curr[i + 1] = m_coords[(i + 1) * m_rot];

		m_curr[i] += midX;
		m_curr[i + 1] += midY;

		if ((m_coords[i] < 0) || (m_coords[i] > 9) || (m_coords[i + 1] > FIELD_SIZE / ROW_LEN))
		{
			for (int i = 0; i < NUM_COORD; i++)
				m_coords[i] = tempArr[i];
			i = NUM_COORD;
		}
	}
}