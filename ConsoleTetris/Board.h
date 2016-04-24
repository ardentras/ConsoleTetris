#pragma once

#define COL_L 0x80
#define COL_B 0x40
#define COL_R 0x20
#define COL_LL 0x10
#define COL_BB 0x08
#define COL_RR 0x04

const int FIELD_SIZE = 220;
const int ROW_LEN = 10;

class Tile;

class Board
{
private:
	int m_level;
	int m_lines;
	int m_score;
	unsigned char m_field[FIELD_SIZE];
	bool m_gameover;
	Tile * m_tile;
	Graphics g;
public:
	Board();
	~Board();
	void DrawField();
	void DrawBoard();
	void ClrTile();
	void DrawTile();
	unsigned char CheckCollision();
	void MoveTile(int dir);
	void SpawnTile();
	
	bool GetGO() { return m_gameover; }
	void SetGO(bool go) { m_gameover = go; }
};

