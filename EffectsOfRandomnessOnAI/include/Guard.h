#ifndef __GUARD_H__
#define __GUARD_H__

#define _USE_MATH_DEFINES

#include "Waypoint.h"
#include "GameStates.h"
#include <stdlib.h>
#include <math.h>

class Guard
{
public:
	Guard() 	//constructor of guard
	{
	}
	~Guard() {}
	void setTargetRotation();	//sets the rotation necessary to move towards the target node
	void update(Randomness &randomness, sf::Vector2f &playerPos, float &resScaler);

	void draw(sf::RenderWindow &window); 	//draws player

	void init(Node* node, sf::Texture &guardTex, sf::Texture &lineOfSightText, std::string fNode, float resScaler); 	//initialises the guard

	void Reset(Node* node, float resScaler); 	//resets the guard back to its original position

	sf::Vector2f m_position; 	//position of the guard on x and y

	sf::Sprite guard; 	//sprite to draw the guard in the game

	sf::Sprite lineOfSight; 	//sprite to draw the guards line of sight in the game

	//nodes to store the previous and next waypoints
	Node previousNode;
	Node targetNode;

	std::list <Node*> highNodes; 	//a list of all nodes for when on high randomness

private:
	Node accessNode;	//node used to check for previous node so it can be deleted (low randomness)
	std::string finalNode;		//sets the final node for randomness level none
	//consts for the angle of each direction
	const int up = 0;
	const int right = 90;
	const int down = 180;
	const int left = 270;

	float currentRotation;
	float targetRotation;

	void move(); 	//moves the guard

	void updateTarget(Randomness &randomness); 	//updates the guards target node

	void rotate(); 	//rotates the guard to face its target node

	void playerdetection(Randomness &randomness, sf::Vector2f playerPos, float &resScaler);	//checks if the player is close enough behind to turn around 

	bool rotating;

	bool forward;	//used to tell which way the guard is going on 'none' randomness

	float m_speed; 	//speed at which the guard will move

	const int detectDist = 90; 	//the distance behind the guard will detect the player

};

#endif //__GUARD_H__
