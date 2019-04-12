#ifndef __WALL_H__
#define __WALL_H__

#include "Source.h"



class Wall
{
public:
	Wall() {} 	//constructor of wall
	Wall(int x, int y, sf::Texture &wallT)
	{
		wall.setTexture(wallT);
		wall.setPosition(x, y);
	}
	~Wall() {}

	sf::Sprite wall;
	void draw(sf::RenderWindow &window); 	//draws the wall
private:
};

#endif //__WALL_H__