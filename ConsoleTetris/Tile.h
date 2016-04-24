#pragma once

const int NUM_COORD = 32;
/*
*	X
*	C
*	X
*	X
*/
const int I_TILE[] = { 0, -1, 0, 0, 0, 1, 0, 2,
					-1, 0, 0, 0, 1, 0, 2, 0,
					0, -1, 0, 0, 0, 1, 0, 2,
					-1, 0, 0, 0, 1, 0, 2, 0 };
/*
*	XX
*	XX
*/
const int O_TILE[] = { 0, 0, 0, 1, 1, 0, 1, 1,
					0, 0, 0, 1, 1, 0, 1, 1,
					0, 0, 0, 1, 1, 0, 1, 1,
					0, 0, 0, 1, 1, 0, 1, 1 };
/*
*	XCX
*	 X
*/
const int T_TILE[] = { -1, 0, 0, 0, 1, 0, 0, 1,
					-1, 0, 0, 0, 0, -1, 0, 1,
					-1, 0, 0, 0, 0, -1, 1, 0,
					0, 1, 0, 0, 0, -1, 1, 0 };
/*
*	X
*	C
*	XX
*/
const int L_TILE[] = { 0, -1, 0, 0, 0, 1, 1, 1,
					-1, 0, 0, 0, 1, 0, -1, 1,
					0, -1, 0, 0, 0, 1, -1, 1,
					-1, 0, 0, 0, 1, 0, 1, -1 };
/*
*	 X
*	 C
*	XX
*/
const int J_TILE[] = { 0, -1, 0, 0, 0, 1, -1, 1,
					-1, 0, 0, 0, 1, 0, -1, -1,
					0, -1, 0, 0, 0, 1, -1, -1,
					-1, 0, 0, 0, 1, 0, 1, 1 };
/*
*	 CX
*	XX
*/
const int S_TILE[] = { 1, 0, 0, 0, 0, 1, -1, 1,
					1, 0, 0, 0, 1, 1, 1, -1,
					1, 0, 0, 0, 0, 1, -1, 1,
					1, 0, 0, 0, 1, 1, 1, -1 };
/*
*	XC
*	 XX
*/
const int Z_TILE[] = { -1, 0, 0, 0, 0, 1, 1, 1,
					0, -1, 0, 0, 0, 1, 1, -1,
					-1, 0, 0, 0, 0, 1, 1, 1,
					0, -1, 0, 0, 0, 1, 1, -1 };

class Tile
{
private:
	int m_coords[NUM_COORD];
	int m_curr[NUM_COORD / 4];
	int m_rot;
	unsigned char m_col;
public:
	Tile(int type);
	~Tile();
	void Drop();
	void MoveLeft();
	void MoveRight();
	void RotLeft();
	void RotRight();

	unsigned char GetCol() { return m_col; }
	int GetCoord(int i) { return m_curr[i]; }
};