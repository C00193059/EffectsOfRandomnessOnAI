#include "Guard.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////initialises the guard
////takes in a node to be used as the current node and set the position of the guard
////takes in the textures for the guard and their line of sight to be assigned to the coresponding sprites
////takes in a string to be used to determine the final node for the 'none' randomness level
void Guard::init(Node* node, sf::Texture &guardTex, sf::Texture &lineOfSightText, std::string fNode, float resScaler)
{

	rotating = true;
	forward = true;
	currentRotation = up;
	targetRotation = up;
	finalNode = fNode;
	m_position = node->position * resScaler;
	previousNode.SetNode(node);
	targetNode.SetNode(node->childNodes.back());	//sets the target node to the last child node of the current node
	guard.setTexture(guardTex);
	lineOfSight.setTexture(lineOfSightText);
	guard.setPosition(m_position);
	guard.setOrigin(sf::Vector2f(25, 25));	//sets the origin to the middle of the image
	guard.scale(sf::Vector2f(resScaler, resScaler));
	lineOfSight.setPosition(m_position);
	lineOfSight.setOrigin(sf::Vector2f(25, 105));	//sets the origin to the bottom of the image to allow for the same position as the guard sprite
	lineOfSight.scale(sf::Vector2f(resScaler, resScaler));
	lineOfSight.setColor(sf::Color(255, 255, 255, 128));
	setTargetRotation();
	m_speed = 2.5 * resScaler;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////resets the guard back to its original state
////used to make the game feel like it started over
////sets the guard back to the position it was when first created (node 1)
void Guard::Reset(Node* node, float resScaler)
{
	rotating = true;
	forward = true;
	currentRotation = up;
	targetRotation = up;
	m_position = node->position * resScaler;
	previousNode.SetNode(node);
	targetNode.SetNode(node->childNodes.back());
	guard.setPosition(m_position);
	guard.setRotation(up);
	lineOfSight.setPosition(m_position);
	lineOfSight.setRotation(up);
	setTargetRotation();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////draws the guard on screen
void Guard::draw(sf::RenderWindow &window)
{
	window.draw(lineOfSight);
	window.draw(guard);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////updates the guard
////takes in randomness to determine what way to select a new waypoint
////takes in player position to determine if the player has walked too close to the guard
void  Guard::update(Randomness &randomness, sf::Vector2f &playerPos, float &resScaler)
{
	playerdetection(randomness, playerPos, resScaler);
	if (!rotating)
	{
		move();
		guard.setPosition(m_position);
		lineOfSight.setPosition(m_position);
		if (m_position.x - targetNode.position.x* resScaler > -4.9 * resScaler && m_position.x - targetNode.position.x* resScaler < 4.9 * resScaler
			&& m_position.y - targetNode.position.y* resScaler >-4.9 * resScaler && m_position.y - targetNode.position.y* resScaler < 4.9 * resScaler)
		{		//checks to see if the guard is less than 1 full movement away from the targetNode
			m_position = targetNode.position * resScaler;	//moves the guard to the target node position to make sure there are no errors
			guard.setPosition(m_position);
			lineOfSight.setPosition(m_position);
			updateTarget(randomness);
		}

	}
	else
	{
		rotate();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////checks to see if the player is close enough behind the guard to turn around
////takes in randomness to make sure the check is not performed on high randomness as it could cause errors
////takes in player position to check the distance from the guard
void Guard::playerdetection(Randomness &randomness, sf::Vector2f playerPos, float &resScaler)
{
	if (randomness != Randomness::High)
	{
		//checks the position of the player depending on the direction of the guard
		if (((targetRotation == up && playerPos.y - m_position.y < detectDist * resScaler  && playerPos.y - m_position.y > 0
			|| targetRotation == down && m_position.y - playerPos.y < detectDist * resScaler  && m_position.y - playerPos.y > 0)
			&& playerPos.x - m_position.x < 25 * resScaler && playerPos.x - m_position.x >-25 * resScaler)
			|| ((targetRotation == left && playerPos.x - m_position.x < detectDist * resScaler && playerPos.x - m_position.x > 0
				|| targetRotation == right && m_position.x - playerPos.x < detectDist * resScaler && m_position.x - playerPos.x > 0)
				&& playerPos.y - m_position.y < 25 * resScaler && playerPos.y - m_position.y >-25 * resScaler))
		{
			//swaps the previous and target nodes
			accessNode = previousNode;
			previousNode = targetNode;
			targetNode = accessNode;
			// keep the rotation value between 0 and 360
			if (targetRotation < 180)
			{
				targetRotation += 180;
			}
			else
			{
				targetRotation -= 180;
			}
			rotating = true;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////chooses the new target node
////takes in randomness to tell how to select the next node
////None: always chooses the last child node until it reaches the final node then always chooses the first child node until it reaches the first node and repeats
////Low: Chooses randomly between the child nodes excluding the previous node
////Medium: Chooses randomly between all the child nodes
////High: Chooses randomly from all the nodes the guard can visit
void Guard::updateTarget(Randomness &randomness)
{
	if (randomness == Randomness::None)
	{
		previousNode.SetNode(&targetNode);
		if (forward)
		{
			targetNode.SetNode(targetNode.childNodes.back());
			if (targetNode.name == finalNode)
			{
				forward = false;
			}
		}
		else
		{
			targetNode.SetNode(*targetNode.childNodes.begin());
			if (targetNode.name == "node1")
			{
				forward = true;
			}
		}
		setTargetRotation();

	}
	///////////////////////////////////////////////////////////////////////////
	else if (randomness == Randomness::Low)
	{
		int noCNones = targetNode.childNodes.size();
		std::list<Node*>::iterator iter = targetNode.childNodes.begin();	//used to access specific child nodes
		for (int i = 0; i < noCNones; i++)
		{
			accessNode.SetNode(*iter);
			if (previousNode.name == accessNode.name)
			{
				targetNode.childNodes.erase(iter);	//removes the previous node to perform the low randomness choice correctly
				break;
			}
			else if (i < noCNones - 1)		//checks to make sure the value wont go out of scope
			{
				std::advance(iter, 1);		// advances the iterator
			}
		}
		noCNones--;
		iter = targetNode.childNodes.begin();
		if (noCNones > 1)
		{
			std::advance(iter, rand() % noCNones);		//chooses randomly from the child nodes
		}
		previousNode.SetNode(&targetNode);
		targetNode.SetNode(*iter);
		setTargetRotation();
	}
	///////////////////////////////////////////////////////////////////////////
	else if (randomness == Randomness::Medium)
	{
		int noCNones = targetNode.childNodes.size();
		std::list<Node*>::iterator iter = targetNode.childNodes.begin();//used to access specific child nodes
		std::advance(iter, rand() % noCNones); //chooses randomly from all the child nodes
		previousNode.SetNode(&targetNode);
		targetNode.SetNode(*iter);
		setTargetRotation();
	}
	///////////////////////////////////////////////////////////////////////////
	else if (randomness == Randomness::High)
	{
		int noCNones = highNodes.size();
		std::list<Node*>::iterator iter = highNodes.begin();//used to access specific child nodes
		std::advance(iter, rand() % noCNones); //chooses randomly from all the nodes
		previousNode.SetNode(&targetNode);
		targetNode.SetNode(*iter);
		setTargetRotation();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////sets the target rotation
////using the position of the next node and the position of the previous node calculates the target rotation
void Guard::setTargetRotation()
{
	targetRotation = atan2(previousNode.position.y - targetNode.position.y, previousNode.position.x - targetNode.position.x);
	targetRotation = targetRotation * 180 / M_PI;
	targetRotation -= 90;	//to accurately reflect the direction the guard wants to go
	if (targetRotation < 0)
	{
		targetRotation += 360;
	}
	if (targetRotation != currentRotation)
	{
		rotating = true;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Rotates the guard when a new target rotation is set
////compares the target rotation to the current rotation to choose how to rotate as to only turn 180 degrees or less
void Guard::rotate()
{

	if ((targetRotation - currentRotation > 0 && targetRotation - currentRotation <= 180) || (targetRotation - currentRotation >= -360 && targetRotation - currentRotation < -180))
	{
		//rotates the sprites
		guard.rotate(7.5f);
		lineOfSight.rotate(7.5f);
		if (guard.getRotation() == 360)
		{	//keeps the rotation between 0 and 360
			guard.setRotation(0.0f);
			lineOfSight.setRotation(0.0f);
		}
	}
	else if ((targetRotation - currentRotation < 0 && targetRotation - currentRotation >= -180) || (targetRotation - currentRotation <= 360 && targetRotation - currentRotation > 180))
	{
		//rotates the sprites
		guard.rotate(-7.5f);
		lineOfSight.rotate(-7.5f);
		if (guard.getRotation() == 0)
		{	//keeps the rotation between 0 and 360
			guard.setRotation(360.0f);
			lineOfSight.setRotation(360.0f);
		}
	}
	//checks to see if the amount left to rotate is less than a full rotation
	if (guard.getRotation() - targetRotation < 7.5f && guard.getRotation() - targetRotation > -7.5f)
	{	//sets the rotations to the target rotation to avoid errors
		guard.setRotation(targetRotation);
		lineOfSight.setRotation(targetRotation);
	}

	if (guard.getRotation() == targetRotation)
	{
		rotating = false;
		currentRotation = targetRotation;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Rotates the guard using m_speed based off their current rotation
void Guard::move()
{
	m_position.x = m_position.x + cos((currentRotation - 90) * M_PI / 180) * m_speed;
	m_position.y = m_position.y + sin((currentRotation - 90) * M_PI / 180) * m_speed;
}