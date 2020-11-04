#include "SceneNode.h"

int polygons;

// destroy all children
SceneNode::~SceneNode()
{
	// loop through and delete children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
		(*i)->Release();

	childList.clear();
}

void SceneNode::AddChild(SceneNode* pNode)
{
	childList.push_back(pNode);
}

void SceneNode::Update()
{
	// loop through the list and update the children
	for (std::list<SceneNode*>::iterator i = childList.begin();
		i != childList.end(); i++)
	{
		(*i)->Update();
	}
}




