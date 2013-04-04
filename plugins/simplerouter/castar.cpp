/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castar.h"
#include "castarnode.h"

#define inherited QObject

/// Construct an empty A* solver instance.
CAStar::CAStar()
: inherited()
{
}


/// Construct an A* solver instance.
/// keepOut An array of points to mark barriers including the area boundary.
/// startPt The starting point.
/// goalPt The goal, or ending point.
CAStar::CAStar(QList<CAStarMarker>& keepOut, QPoint startPt, QPoint goalPt)
: inherited()
, mKeepoutList(keepOut)
, mStartPt(startPt)
, mGoalPt(goalPt)
{
}

/// Copy constructor
CAStar::CAStar(const CAStar& other)
: inherited()
{
	if ( this != &other )
	{
		mStartPt        = other.mStartPt;
		mGoalPt         = other.mGoalPt;
		mOpenList       = other.mOpenList;
		mClosedList     = other.mClosedList;
		mKeepoutList    = other.mKeepoutList;
	}
}

/// Destructor
CAStar::~CAStar()
{
	clear();
}

/// seek the path with parameters.
/// keepOut An array of points to mark barriers including the area boundary.
/// startPt The starting point.
/// goalPt The goal, or ending point.
QList<CAStarNode> CAStar::path(QList<CAStarMarker>& keepOut, QPoint startPt, QPoint goalPt)
{
	mKeepoutList = keepOut;
	mStartPt = startPt;
	mGoalPt = goalPt;
	return path();
}

/// seek the path.
QList<CAStarNode> CAStar::path()
{
	int idx;
	QList<CAStarNode> rc;
	CAStarNode node(mStartPt);
	insort(mOpenList,node);
	while(!mOpenList.isEmpty() && (node = mOpenList.takeFirst()) != mGoalPt )
	{
		QList<CAStarNode> children = childList(node);
		for(int n=0; n < children.count(); n++)
		{
			CAStarNode child = children[n];
			// child node already in the open list?
			int oIdx = mOpenList.indexOf(child);
			if ( oIdx >=0 )
			{
				// the existing node is better?
				CAStarNode other = mOpenList[oIdx];
				if ( other <= child )
					continue;
			}
			// child node already in the closed list?
			int cIdx = mClosedList.indexOf(child);
			if ( cIdx >= 0 )
			{
				// the existing node is better?
				CAStarNode other = mClosedList[cIdx];
				if ( other <= child )
					continue;
			}
			// remove child from open and closed lists
			if ( oIdx >= 0 )
				mOpenList.takeAt(oIdx);
			if ( cIdx >= 0 )
				mClosedList.takeAt(cIdx);
			// add child to open list
			insort(mOpenList,child);

		}
		insort(mClosedList,node);
	}
	// follow parent nodes from goal back to start
	do
	{
		CAStarNode other(node.parent());
		rc.append(node);
		if ( ( idx = mClosedList.indexOf( other ) ) >= 0 )
			other = mClosedList.takeAt(idx);
		else
		if ( ( idx = mOpenList.indexOf( other ) ) >= 0 )
			other = mOpenList.takeAt(idx);
		else
			break;
		node = other;
	} while( !isEmpty(node.pos()) );
	return rc;
}

/// clear the open/closed lists
void CAStar::clear()
{
	while(!mOpenList.isEmpty())
	{
		CAStarNode node = mOpenList.takeLast();
	}
	while(!mClosedList.isEmpty())
	{
		CAStarNode node = mClosedList.takeLast();
	}
	while(!mKeepoutList.isEmpty())
	{
		CAStarMarker node = mKeepoutList.takeLast();
	}
}

/// create a child list
QList<CAStarNode> CAStar::childList(CAStarNode& node)
{
	QList<CAStarNode> rc;
	for(int x=-1; x<=1; x++)
	{
		for(int y=-1; y<=1; y++)
		{
			CAStarNode child(QPoint(node.pos().x()+x,node.pos().y()+y),node.pos());
			if ( mKeepoutList.indexOf(child) < 0 )
			{
				child.setCost( cost( child, node ) );
				rc.append(child);
			}
		}
	}
	return rc;
}

/// return the index of a node based on a point
int CAStar::nodeIndex(QList<CAStarNode>& list,QPoint pt)
{
	int count = list.count();
	for(int idx=0; idx < count; idx++)
	{
		if ( list[idx] == pt )
			return idx;
	}
	return -1;
}

/// Transfer a node to the open list.
void CAStar::open(CAStarNode& node)
{
	int idx;
	if ( (idx=mClosedList.indexOf(node))>= 0 )
		mClosedList.takeAt(idx);
	if ( (idx=mOpenList.indexOf(node))>= 0 )
		mOpenList.replace(idx,node);
	else
		insort(mOpenList,node);
}

/// Transfer a node to the closed list.
void CAStar::close(CAStarNode& node)
{
	int idx;
	if ( (idx=mOpenList.indexOf(node))>= 0 )
		mOpenList.takeAt(idx);
	if ( (idx=mClosedList.indexOf(node))>= 0 )
		mClosedList.replace(idx,node);
	else
		insort(mClosedList,node);
}

/// Returns the sum of the absolute values of x() and y(), traditionally known as the "Manhattan length"
/// of the vector from the origin to the point.
double CAStar::manhattanLength(QPoint a, QPoint b)
{
	QPoint delta = (b - a);
	return delta.manhattanLength();
}

/// Calculate the cost between two adjacent points.
/// We will assign a cost of 10 to each horizontal or vertical square moved, and a cost of 14.14 for a diagonal move.
/// We use these numbers because the actual distance to move diagonally is the square root of 2,
/// or roughly 1.414 times the cost of moving horizontally or vertically.
double CAStar::adjacentCost(QPoint a, QPoint b)
{
	double diffX = abs(a.x()-b.x());
	double diffY = abs(a.y()-b.y());
	double rc = ( diffX && diffY ) ? 14 : 10;
	return rc;
}

/// insert a child into the list sorted by cost.
void CAStar::insort(QList<CAStarNode>& list, CAStarNode& node)
{
	int idx = list.indexOf(node);
	if ( idx < 0 ) // insorted already?
	{
		for(int n=0; n < list.length(); n++)
		{
			CAStarNode other = list[n];
			if ( node < other )
			{
				list.insert(n,node);
				return;
			}
		}
		list.append(node);
	}
}

/// Calculate the cost of this node
double CAStar::cost(CAStarNode node, CAStarNode parent)
{
	double rc = g(node,parent) + h(node);
	return rc;
}

/// Calculate G, the movement cost to move from the starting point A
/// to this cell of the grid, following the path generated to get there.
double CAStar::g(CAStarNode node, CAStarNode parent)
{
	double rc=adjacentCost(node.pos(),parent.pos());
	node = parent;
	while( !isEmpty( node.parent() ) )
	{
		CAStarNode other(node.parent());
		rc += adjacentCost( other.pos(), node.pos() );
		node = other;
	}
	return rc;
}

/// The estimated movement cost to move from that given square on the grid to the final destination
double CAStar::h(CAStarNode node)
{
	double rc = manhattanLength( node.pos(), mGoalPt ) * 10.0;
	return rc;
}

/// Is the point empty - unset?
bool CAStar::isEmpty(QPoint pt)
{
	return ( pt.x() == EMPTY_X && pt.y() == EMPTY_Y );
}
