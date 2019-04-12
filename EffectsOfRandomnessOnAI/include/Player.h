#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Source.h"


class Player
{
public:

	Player(); 	//constructor of player
	~Player();

	void update(bool collision);

	void draw(sf::RenderWindow &window); 	//draws player

	void keyEvents(sf::RenderWindow &window); 	//detects key inputs for moving the player

	void Reset();

	sf::Vector2f m_position; 	//position of player on x and y
	//sprite to draw the player in the game
	sf::Sprite player;
	sf::Texture playerTex;


private:
	//consts for the angle of each direction
	const int up = 0;
	const int right = 90;
	const int down = 180;
	const int left = 270;

	float currentRotation;
	float targetRotation;

	void movementLeft();
	void movementRight();
	void movementUp();
	void movementDown();

	void rotate();	//when a new direction is pressed rotate to that direction
	bool rotating;
	//bools used to keep track of if a key for a direction is still being held or just pressed
	bool leftClick;
	bool rightClick;
	bool upClick;
	bool downClick;

	float m_speed; 	//speed at which the player will move
};

#endif //__PLAYER_H__