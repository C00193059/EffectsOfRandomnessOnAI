#ifndef __WAYPOINT_H__
#define __WAYPOINT_H__
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <iostream>
#include <list> 


class Node
{
public:

	Node() {}
	Node(int x, int y, sf::String n)
	{
		position = sf::Vector2f(x,y);
		name = n;
	}
	~Node() {}

	std::list <Node*> childNodes;	//list of pointers to the nodes connected to the current node
	sf::Vector2f position;

	std::string name;	//name of the current node. Used to check if nodes are the same

	void SetNode(Node* n); 	//sets the current node to be the passed in node

private:

};

#endif //__WAYPOINT_H__