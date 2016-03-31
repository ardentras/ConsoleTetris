#pragma once

const int FIELD_SIZE = 220;
const int ROW_LEN = 10;

class Board
{
private:
	int m_level;
	int m_lines;
	int m_score;
	unsigned char m_field[FIELD_SIZE];
	bool m_gameover;
	Graphics g;
public:
	Board();
	~Board();
	void DrawField();
	void DrawBoard();
	void DropTile();
	void MoveTile(int dir);
	void SpawnTet();
	void AddToBoard(int grid[]);
	
	bool GetGO();
	void SetGO(bool go);
};

