/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarpath.h"

CAStarPath::CAStarPath()
{
}

CAStarPath::~CAStarPath()
{
}

CAStarPath::tNodeList CAStarPath::seek(CAStarNode& startNode, CAStarNode& endNode)
{
	tNodeList	path;

	// FIXME - initialize node parameters and initiate node seek....

	return path;
}

bool CAStarPath::contains(tNodeList& nodeList, CAStarNode& node)
{
	bool rc=false;
	for (int j = 0; !rc && j < nodeList.size(); ++j)
	{
		rc = (nodeList[j] == node);
	}
	return rc;
}

int CAStarPath::heuristic(CAStarNode &goal, CAStarNode& node)
{
	int xDistance = abs(node.x() - goal.x());
	int yDistance = abs(node.y() - goal.y());
	int rc = 10 * (xDistance + yDistance);			// FIXME
	return rc;
}
