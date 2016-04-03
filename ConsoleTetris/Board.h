#pragma once

#define COL_L 0x80
#define COL_B 0x40
#define COL_R 0x20
#define COL_LL 0x10
#define COL_BB 0x08
#define COL_RR 0x04

const int FIELD_SIZE = 220;
const int ROW_LEN = 10;
const int NUM_COORD = 8;

class Board
{
private:
	int m_level;
	int m_lines;
	int m_score;
	unsigned char m_field[FIELD_SIZE];
	int currCoords[8];
	bool m_gameover;
	Graphics g;
public:
	Board();
	~Board();
	void DrawField();
	void DrawBoard();
	void DropTile();
	void ClrTile();
	unsigned char CheckCollision();
	void MoveLeft();
	void MoveRight();
	void RotLeft();
	void RotRight();
	void MoveTile(int dir);
	void SpawnTet();
	void AddToBoard(unsigned char col);
	
	bool GetGO();
	void SetGO(bool go);
};

