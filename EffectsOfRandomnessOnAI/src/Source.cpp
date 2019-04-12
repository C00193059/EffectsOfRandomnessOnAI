#include "Source.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Niall Dunne
////C00193059
////Effects of Randomness on AI
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sf::RenderWindow window(sf::VideoMode(950, 750), "Effects of Randomness on AI");//create window for the game


//used to cap the framerate
sf::Clock fpsClock;
sf::Time timeSinceLastUpdate = sf::Time::Zero;
sf::Time timePerFrame = sf::seconds(1.f / 60.f);

//create instance of game state and set it to main menu
GameStates m_gameState = GameStates::MainMenu;
//initialises randomness
Randomness m_randomness = Randomness::None;
////////////////////////////////////////////////////////////////
bool rPressed = false;

Player player;

sf::Event event;

std::list <Wall> walls;	//used to store all the walls

sf::Vector2f tempPos;

Guard guard1;
Guard guard2;
Guard guard3;
////////////////////////////////////////////////////////////////
//create all the sprites and textures used in the game
sf::Sprite background;
sf::Texture backgroundText;
sf::Sprite mainMenu;
sf::Texture mainMenuText;
sf::Sprite win;
sf::Texture winText;
sf::Sprite lose;
sf::Texture loseText;
sf::Sprite goal;
sf::Texture goalText;
sf::Texture wallText;
sf::Texture guardTex;
sf::Texture lineOfSightText;
////////////////////////////////////////////////////////////////
//creates the font and randomness strings
sf::Font font;
sf::Text randText;
sf::String strRandNone = "None";
sf::String strRandLow = "Low";
sf::String strRandMedium = "Medium";
sf::String strRandHigh = "High";
////////////////////////////////////////////////////////////////
//creates all the nodes for guard 1 and gives the a position
Node guard1Node1(75, 675, "node1");
Node guard1Node2(75, 475, "node2");
Node guard1Node3(275, 675, "node3");
Node guard1Node4(275, 475, "node4");
Node guard1Node5(425, 675, "node5");
Node guard1Node6(425, 475, "node6");
Node guard1Node7(525, 675, "node7");
Node guard1Node8(525, 475, "node8");
Node guard1Node9(675, 675, "node9");
Node guard1Node10(675, 475, "node10");
Node guard1Node11(875, 675, "node11");
Node guard1Node12(875, 475, "node12");
////////////////////////////////////////////////////////////////
//creates all the nodes for guard 2 and gives the a position
Node guard2Node1(75, 75, "node1");
Node guard2Node2(75, 225, "node2");
Node guard2Node3(75, 375, "node3");
Node guard2Node4(225, 375, "node4");
Node guard2Node5(225, 225, "node5");
Node guard2Node6(225, 75, "node6");
Node guard2Node7(375, 75, "node7");
Node guard2Node8(375, 225, "node8");
Node guard2Node9(375, 375, "node9");
////////////////////////////////////////////////////////////////
//creates all the nodes for guard 3 and gives the a position
Node guard3Node1(575, 175, "node1");
Node guard3Node2(725, 175, "node2");
Node guard3Node3(875, 175, "node3");
Node guard3Node4(875, 275, "node4");
Node guard3Node5(725, 275, "node5");
Node guard3Node6(575, 275, "node6");
Node guard3Node7(575, 375, "node7");
Node guard3Node8(725, 375, "node8");
Node guard3Node9(875, 375, "node9");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Checks for collision between the player and any of the walls
////takes in the sprite for the player and the position they are trying to move to and checks to see if in that position if the player would collide with a wall
////iterates through the list of walls to check each one
////if there is a collision 'true' is returned to be used to stop the player moving that way
////if there is no collision false is returned
bool WallCollisionDetection(sf::Sprite &sprite, sf::Vector2f &position)
{
	if (sprite.getPosition() != position)
	{
		tempPos = sprite.getPosition();
		sprite.setPosition(position);
		for (auto v : walls)
		{
			if (v.wall.getGlobalBounds().intersects(sprite.getGlobalBounds()))
			{
				sprite.setPosition(tempPos);
				return true;
			}
		}
		sprite.setPosition(tempPos);
		return false;
	}
	else
	{
		return false;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Initialises the child nodes for all of the nodes for each guard
////fills the list off all the nodes for each guard to be used in the high randomness
void NodeInit()
{
	guard1Node1.childNodes.push_back(&guard1Node3);
	guard1Node1.childNodes.push_back(&guard1Node2);

	guard1Node2.childNodes.push_back(&guard1Node1);
	guard1Node2.childNodes.push_back(&guard1Node4);

	guard1Node3.childNodes.push_back(&guard1Node4);
	guard1Node3.childNodes.push_back(&guard1Node1);
	guard1Node3.childNodes.push_back(&guard1Node5);

	guard1Node4.childNodes.push_back(&guard1Node2);
	guard1Node4.childNodes.push_back(&guard1Node6);
	guard1Node4.childNodes.push_back(&guard1Node3);

	guard1Node5.childNodes.push_back(&guard1Node3);
	guard1Node5.childNodes.push_back(&guard1Node7);
	guard1Node5.childNodes.push_back(&guard1Node6);

	guard1Node6.childNodes.push_back(&guard1Node5);
	guard1Node6.childNodes.push_back(&guard1Node4);
	guard1Node6.childNodes.push_back(&guard1Node8);

	guard1Node7.childNodes.push_back(&guard1Node8);
	guard1Node7.childNodes.push_back(&guard1Node5);
	guard1Node7.childNodes.push_back(&guard1Node9);

	guard1Node8.childNodes.push_back(&guard1Node6);
	guard1Node8.childNodes.push_back(&guard1Node10);
	guard1Node8.childNodes.push_back(&guard1Node7);

	guard1Node9.childNodes.push_back(&guard1Node7);
	guard1Node9.childNodes.push_back(&guard1Node11);
	guard1Node9.childNodes.push_back(&guard1Node10);

	guard1Node10.childNodes.push_back(&guard1Node9);
	guard1Node10.childNodes.push_back(&guard1Node8);
	guard1Node10.childNodes.push_back(&guard1Node12);

	guard1Node11.childNodes.push_back(&guard1Node12);
	guard1Node11.childNodes.push_back(&guard1Node9);

	guard1Node12.childNodes.push_back(&guard1Node10);
	guard1Node12.childNodes.push_back(&guard1Node11);

	////////////////////////////////////////////////////////////////
	guard1.highNodes.push_back(&guard1Node1);
	guard1.highNodes.push_back(&guard1Node2);
	guard1.highNodes.push_back(&guard1Node3);
	guard1.highNodes.push_back(&guard1Node4);
	guard1.highNodes.push_back(&guard1Node5);
	guard1.highNodes.push_back(&guard1Node6);
	guard1.highNodes.push_back(&guard1Node7);
	guard1.highNodes.push_back(&guard1Node8);
	guard1.highNodes.push_back(&guard1Node9);
	guard1.highNodes.push_back(&guard1Node10);
	guard1.highNodes.push_back(&guard1Node11);
	guard1.highNodes.push_back(&guard1Node12);
	////////////////////////////////////////////////////////////////
	guard2Node1.childNodes.push_back(&guard2Node6);
	guard2Node1.childNodes.push_back(&guard2Node2);

	guard2Node2.childNodes.push_back(&guard2Node1);
	guard2Node2.childNodes.push_back(&guard2Node5);
	guard2Node2.childNodes.push_back(&guard2Node3);

	guard2Node3.childNodes.push_back(&guard2Node2);
	guard2Node3.childNodes.push_back(&guard2Node4);

	guard2Node4.childNodes.push_back(&guard2Node3);
	guard2Node4.childNodes.push_back(&guard2Node9);
	guard2Node4.childNodes.push_back(&guard2Node5);

	guard2Node5.childNodes.push_back(&guard2Node4);
	guard2Node5.childNodes.push_back(&guard2Node2);
	guard2Node5.childNodes.push_back(&guard2Node8);
	guard2Node5.childNodes.push_back(&guard2Node6);

	guard2Node6.childNodes.push_back(&guard2Node5);
	guard2Node6.childNodes.push_back(&guard2Node1);
	guard2Node6.childNodes.push_back(&guard2Node7);

	guard2Node7.childNodes.push_back(&guard2Node6);
	guard2Node7.childNodes.push_back(&guard2Node8);

	guard2Node8.childNodes.push_back(&guard2Node7);
	guard2Node8.childNodes.push_back(&guard2Node5);
	guard2Node8.childNodes.push_back(&guard2Node9);

	guard2Node9.childNodes.push_back(&guard2Node8);
	guard2Node9.childNodes.push_back(&guard2Node4);

	////////////////////////////////////////////////////////////////
	guard2.highNodes.push_back(&guard2Node1);
	guard2.highNodes.push_back(&guard2Node2);
	guard2.highNodes.push_back(&guard2Node3);
	guard2.highNodes.push_back(&guard2Node4);
	guard2.highNodes.push_back(&guard2Node5);
	guard2.highNodes.push_back(&guard2Node6);
	guard2.highNodes.push_back(&guard2Node7);
	guard2.highNodes.push_back(&guard2Node8);
	guard2.highNodes.push_back(&guard2Node9);
	////////////////////////////////////////////////////////////////
	guard3Node1.childNodes.push_back(&guard3Node6);
	guard3Node1.childNodes.push_back(&guard3Node2);

	guard3Node2.childNodes.push_back(&guard3Node1);
	guard3Node2.childNodes.push_back(&guard3Node5);
	guard3Node2.childNodes.push_back(&guard3Node3);

	guard3Node3.childNodes.push_back(&guard3Node2);
	guard3Node3.childNodes.push_back(&guard3Node4);

	guard3Node4.childNodes.push_back(&guard3Node3);
	guard3Node4.childNodes.push_back(&guard3Node9);
	guard3Node4.childNodes.push_back(&guard3Node5);

	guard3Node5.childNodes.push_back(&guard3Node4);
	guard3Node5.childNodes.push_back(&guard3Node2);
	guard3Node5.childNodes.push_back(&guard3Node8);
	guard3Node5.childNodes.push_back(&guard3Node6);

	guard3Node6.childNodes.push_back(&guard3Node5);
	guard3Node6.childNodes.push_back(&guard3Node1);
	guard3Node6.childNodes.push_back(&guard3Node7);

	guard3Node7.childNodes.push_back(&guard3Node6);
	guard3Node7.childNodes.push_back(&guard3Node8);

	guard3Node8.childNodes.push_back(&guard3Node7);
	guard3Node8.childNodes.push_back(&guard3Node5);
	guard3Node8.childNodes.push_back(&guard3Node9);

	guard3Node9.childNodes.push_back(&guard3Node8);
	guard3Node9.childNodes.push_back(&guard3Node4);
	////////////////////////////////////////////////////////////////
	guard3.highNodes.push_back(&guard3Node1);
	guard3.highNodes.push_back(&guard3Node2);
	guard3.highNodes.push_back(&guard3Node3);
	guard3.highNodes.push_back(&guard3Node4);
	guard3.highNodes.push_back(&guard3Node5);
	guard3.highNodes.push_back(&guard3Node6);
	guard3.highNodes.push_back(&guard3Node7);
	guard3.highNodes.push_back(&guard3Node8);
	guard3.highNodes.push_back(&guard3Node9);
	////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////calls the reset functions for all the guards and the player
void Reset()
{
	guard1.Reset(&guard1Node1);
	guard2.Reset(&guard2Node1);
	guard3.Reset(&guard3Node1);
	player.Reset();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////increases the level of randomness by 1 at a time
////changing at high returns to none
////updates the text on screen to reflect the new randomness
void ChangeRandomness()
{
	if (m_randomness == Randomness::None)
	{
		m_randomness = Randomness::Low;
		randText.setString("Randomness : " + strRandLow);
	}
	else if (m_randomness == Randomness::Low)
	{
		m_randomness = Randomness::Medium;
		randText.setString("Randomness : " + strRandMedium);
	}
	else if (m_randomness == Randomness::Medium)
	{
		m_randomness = Randomness::High;
		randText.setString("Randomness : " + strRandHigh);
	}
	else if (m_randomness == Randomness::High)
	{
		m_randomness = Randomness::None;
		randText.setString("Randomness : " + strRandNone);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////Checks to see if the player has reached the goal
////if they have change the gamestate to the win screen, increase the randomness and call the reset function
void GoalCollisionDetection()
{
	if (goal.getGlobalBounds().intersects(player.player.getGlobalBounds()))
	{
		Reset();
		ChangeRandomness();
		m_gameState = GameStates::WinScreen;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////checks to see if the player collided with any of the guards or walked into their line of sight
////Guard collisions are only checked in that guards area so as to not colide with guards line of sight on the opposite side of the wall
////if the player has collided with a guard or line of sight change the gamestate to the lose screen and call the reset function 
void GuardCollisionDetection()
{
	if ((guard1.guard.getGlobalBounds().intersects(player.player.getGlobalBounds()) || guard1.lineOfSight.getGlobalBounds().intersects(player.player.getGlobalBounds())
		&& player.m_position.y > 450)||
		(guard2.guard.getGlobalBounds().intersects(player.player.getGlobalBounds()) || guard2.lineOfSight.getGlobalBounds().intersects(player.player.getGlobalBounds())
			&& player.m_position.y < 400 && player.m_position.x < 400) ||
		(guard3.guard.getGlobalBounds().intersects(player.player.getGlobalBounds()) || guard3.lineOfSight.getGlobalBounds().intersects(player.player.getGlobalBounds())
			&& player.m_position.y < 400) && player.m_position.x > 550)
	{
		Reset();
		m_gameState = GameStates::LoseScreen;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////main() starts//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	fpsClock.restart();
	srand(time(NULL));	//seeds the random number generator
	NodeInit();
	//loads in all the textures for the game
	if (!font.loadFromFile("calibri.ttf"))
	{
		std::cout << "Error loading Font" << std::endl;
	}
	if (!guardTex.loadFromFile("Guard1.png"))
	{
		std::cout << "Error loading guards" << std::endl;
	}
	if (!mainMenuText.loadFromFile("MainMenu.png"))
	{
		std::cout << "Error loading menu screen" << std::endl;
	}
	if (!winText.loadFromFile("Win.png"))
	{
		std::cout << "Error loading win screen" << std::endl;
	}
	if (!loseText.loadFromFile("Lose.png"))
	{
		std::cout << "Error loading lose screen" << std::endl;
	}
	if (!lineOfSightText.loadFromFile("GuardLineOfSight.png"))
	{
		std::cout << "Error loading line of sight" << std::endl;
	}
	if (!wallText.loadFromFile("Wall2.png"))
	{
		std::cout << "Error loading walls" << std::endl;
	}
	if (!goalText.loadFromFile("Goal.png"))
	{
		std::cout << "Error loading goal" << std::endl;
	}
	if (!backgroundText.loadFromFile("Background.png"))
	{
		std::cout << "Error loading background" << std::endl;
	}

	randText.setFont(font);	// set the font
	randText.setString("Randomness : " + strRandNone);	// set the string to display
	randText.setCharacterSize(50);
	randText.setFillColor(sf::Color::White);
	randText.setStyle(sf::Text::Bold);
	randText.setPosition(450, 690);
	//initialise the guards
	guard1.init(&guard1Node1, guardTex, lineOfSightText, "node11");
	guard2.init(&guard2Node1, guardTex, lineOfSightText, "node9");
	guard3.init(&guard3Node1, guardTex, lineOfSightText, "node9");
	//set the textures for the sprites
	background.setTexture(backgroundText);
	mainMenu.setTexture(mainMenuText);
	win.setTexture(winText);
	lose.setTexture(loseText);
	goal.setTexture(goalText);
	goal.setPosition(550, 50);

	int grid[19][15] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},         //the 2D array used to design the map and create all the walls
		{1,0,0,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,0,1,1,0,1,1,0,0,0,1,1,1,0,1},
		{1,0,1,1,0,1,1,0,1,0,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,0,1,1,0,1,1,0,1,0,0,0,0,0,1},
		{1,0,1,1,0,1,1,0,1,0,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,1,0,1,1,1,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,1,1,1,1,1,0,1,1,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
		{1,0,1,0,1,0,1,0,1,0,0,0,0,0,1},
		{1,0,1,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
		{1,0,0,0,1,0,1,0,1,0,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	for (int x = 0; x < 19; x++)	//iterates through each element in the 2D array
	{
		for (int y = 0; y < 15; y++)
		{
			if (grid[x][y] == 1)
			{	
				walls.push_back(Wall(x * 50, y * 50, wallText));	//if there is a 1 put a wall in that position
			}
		}
	}
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		//get the time since last update and restart the clock
		timeSinceLastUpdate += fpsClock.restart();

		if (m_gameState == GameStates::MainMenu || m_gameState == GameStates::WinScreen || m_gameState == GameStates::LoseScreen)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_gameState = GameStates::Play;
			}
		}
		else if (m_gameState == GameStates::Play)
		{
			if (timeSinceLastUpdate > timePerFrame)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					if (!rPressed)
					{	//used to make sure when the key is only pressed once the action only happens once
						ChangeRandomness();
						rPressed = true;
					}
				}
				else if (rPressed)	//used to make sure when the key is only pressed once the action only happens once
				{
					rPressed = false;
				}
				player.keyEvents(window);
				player.update(WallCollisionDetection(player.player, player.m_position));
				guard1.update(m_randomness, player.m_position);
				guard2.update(m_randomness, player.m_position);
				guard3.update(m_randomness, player.m_position);
				GoalCollisionDetection();
				GuardCollisionDetection();

				// reset the timeSinceLastUpdate to 0 
				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
		//all the drawing of game assets is completed here
		window.clear();

		if (m_gameState == GameStates::MainMenu)
		{
			window.draw(mainMenu);
		}
		else if (m_gameState == GameStates::LoseScreen)
		{
			window.draw(lose);
		}
		else if (m_gameState == GameStates::WinScreen)
		{
			window.draw(win);
		}
		else if (m_gameState == GameStates::Play)
		{
			window.draw(background);
			window.draw(goal);
			for (auto v : walls)
			{
				v.draw(window);
			}
			player.draw(window);
			guard1.draw(window);
			guard2.draw(window);
			guard3.draw(window);
			window.draw(randText);
		}
		window.display();

	}

	return 0;

}