#ifndef __WALL_H__
#define __WALL_H__

#include "Source.h"



class Wall
{
public:
	Wall() {} 	//constructor of wall
	Wall(float x, float y, sf::Texture &wallT, float resScaler)
	{
		wall.setTexture(wallT);
		wall.setPosition(x, y);
		wall.scale(sf::Vector2f(resScaler, resScaler));
	}
	~Wall() {}

	sf::Sprite wall;
	void draw(sf::RenderWindow &window); 	//draws the wall
private:
};

#endif //__WALL_H__