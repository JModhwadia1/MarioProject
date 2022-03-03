#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "constant.h"


class LevelMap
{
public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();
	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int new_value);

	int GetTileAt(unsigned int h, unsigned int w);
private:
	int** m_map;
};
#endif // !_LEVELMAP_H

