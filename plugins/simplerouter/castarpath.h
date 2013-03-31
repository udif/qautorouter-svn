/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARPATH_H
#define _CASTARPATH_H

#include <QObject>
#include <QList>
#include "castarnode.h"

class CAStarPath
{
	public:
		CAStarPath();
		~CAStarPath();

		typedef QList<CAStarNode> tNodeList;

		tNodeList	seek(CAStarNode& startNode, CAStarNode& endNode);

	private:

		bool		contains(tNodeList& nodeList, CAStarNode& node);
		int			heuristic(CAStarNode& goal, CAStarNode& node);

};

#endif // _CASTARPATH_H
