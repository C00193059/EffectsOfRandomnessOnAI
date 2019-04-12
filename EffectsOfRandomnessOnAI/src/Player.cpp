#include "Player.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Default constructor for the player
////loads in and sets the players sprite
Player::Player()
{
	if (!playerTex.loadFromFile("Player1.png"))
	{
		std::cout << "Error loading player" << std::endl;
	}
	currentRotation = 0;
	targetRotation = 0;
	player.setTexture(playerTex);
	player.setOrigin(sf::Vector2f(15.0f, 15.0f));	//sets the sprites origin to the centre of the image
	//set position of the player
	m_position = sf::Vector2f(880, 680);
	player.setPosition(m_position);
	m_speed = 5.0;	//set the speed of the player
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Resets the player back to their initial state
void Player::Reset()
{
	currentRotation = 0;
	targetRotation = 0;
	//set position of the player
	m_position = sf::Vector2f(880, 680);
	player.setPosition(m_position);
	player.setRotation(0);
}
Player::~Player()
{
	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////draws the player on screen
void Player::draw(sf::RenderWindow &window)
{
		window.draw(player);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Updates the player
////takes in a bool that is set true if the player is about to collide with a wall
////stops this by only moving the player in a direction that won't colide with a wall
void Player::update(bool collision)
{
	if (collision)
	{
		m_position = player.getPosition();
	}
	if (player.getPosition() != m_position && !collision)
	{	//if the player has tried to move and it wont involve hitting a wall move them
		player.setPosition(m_position);
	}
	if (rotating)
	{
		rotate();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Rotates the player when a new direction is pressed
////compares the target rotation to the current rotation to choose how to rotate as to only turn 180 degrees or less
void Player::rotate()
{
	if (targetRotation - currentRotation == 90 || targetRotation - currentRotation == 180 || targetRotation - currentRotation == -270)
	{
		player.rotate(15.0f);	//rotates the sprite
		if (player.getRotation() == 360)
		{	//keeps the rotation between 0 and 360
			player.setRotation(0.0f);
		}
	}
	else if (targetRotation - currentRotation == -90 || targetRotation - currentRotation == -180 || targetRotation - currentRotation == 270)
	{
		if (player.getRotation() == 0)
		{	//keeps the rotation between 0 and 360
			player.setRotation(360.0f);
		}
		player.rotate(-15.0f); 	//rotates the sprite
	}

	if (player.getRotation() == targetRotation)
	{
		rotating = false;
		currentRotation = targetRotation;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////controls what happens when the player presses a key
////when each directional key is pressed only move/rotate the player when its not already rotating
////only rotates the playerin the direction pressed if its the only direction pressed or its the last direction pressed and it wasnt already pressed
void Player::keyEvents(sf::RenderWindow &window)
{
		//if the left key is pressed move the player left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (currentRotation == left && !rotating)
		{
			movementLeft();
		}
		if (currentRotation != left && !rotating && !rightClick && !upClick && !downClick)
		{
			rotating = true;
			targetRotation = left;
			leftClick = true;
		}

		else if (currentRotation != left && !rotating && !leftClick && (rightClick || upClick || downClick))
		{
			rotating = true;
			targetRotation = left;
			leftClick = true;
		}
	}
	else if (leftClick)
	{
		leftClick = false;
	}
		//if the right key is pressed move the player right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (currentRotation == right && !rotating)
		{
			movementRight();
		}
		if (currentRotation != right && !rotating && !leftClick && !upClick && !downClick)
		{
			rotating = true;
			targetRotation = right;
			rightClick = true;
		}

		else if (currentRotation != right && !rotating && !rightClick && (leftClick || upClick || downClick))
		{
			rotating = true;
			targetRotation = right;
			rightClick = true;
		}
	}
	else if (rightClick)
	{
		rightClick = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (currentRotation == up && !rotating)
		{
			movementUp();
		}
		if (currentRotation != up && !rotating && !leftClick && !rightClick && !downClick)
		{
			rotating = true;
			targetRotation = up;
			upClick = true;
		}

		else if (currentRotation != up && !rotating && !upClick && (leftClick || rightClick || downClick))
		{
			rotating = true;
			targetRotation = up;
			upClick = true;
		}
	}
	else if (upClick)
	{
		upClick = false;
	}
		 //if the right key is pressed move the player right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (currentRotation == down && !rotating)
		{
			movementDown();
		}
		if (currentRotation != down && !rotating && !leftClick && !rightClick && !upClick)
		{
			rotating = true;
			targetRotation = down;
			downClick = true;
		}

		else if (currentRotation != down && !rotating && !downClick && (leftClick || rightClick || upClick))
		{
			rotating = true;
			targetRotation = down;
			downClick = true;
		}
	}
	else if (downClick)
	{
		downClick = false;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////moves the player left
void Player::movementLeft()
{
	m_position.x = player.getPosition().x - m_speed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////moves the player right
void Player::movementRight()
{
	m_position.x = player.getPosition().x + m_speed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////moves the player up
void Player::movementUp()
{
	m_position.y = player.getPosition().y - m_speed;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////moves the player down
void Player::movementDown()
{
	m_position.y = player.getPosition().y + m_speed;
}