#include "Waypoint.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////sets all variables in the current node to be equal to the passed in node
void Node::SetNode(Node* n)
{
	position = n->position;
	name = n->name;
	childNodes.clear();		//removes all the old child nodes before assigning the new ones
	for (auto cN : n->childNodes)
	{
		childNodes.push_back(cN);
	}
}