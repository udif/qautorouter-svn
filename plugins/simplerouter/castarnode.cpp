/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarnode.h"
#include <math.h>

QRectF			CAStarNode::mBounds;
QPointF			CAStarNode::mStart;
QPointF			CAStarNode::mGoalPt;
QRectF			CAStarNode::mGoalRect;
QGraphicsScene*	CAStarNode::mScene=NULL;
double			CAStarNode::mGridRez=1.0;

CAStarNode::CAStarNode(CAStarNode* parent)
: mParent(parent)
, mCost(0.0)
, mOpen(true)
, mG(0.0)
, mH(0.0)
{
}

CAStarNode::CAStarNode(QPointF pt, CAStarNode* parent)
: mParent(parent)
, mPos(pt)
, mCost(0.0)
, mOpen(true)
, mG(0.0)
, mH(0.0)
{
}

CAStarNode::CAStarNode(QPointF pt, double cost, CAStarNode* parent)
: mParent(parent)
, mPos(pt)
, mCost(cost)
, mOpen(true)
, mG(0.0)
, mH(0.0)
{
}

CAStarNode::CAStarNode(const CAStarNode& other)
: mParent(other.mParent)
, mPos(other.mPos)
, mCost(other.mCost)
, mOpen(true)
, mG(0.0)
, mH(0.0)
{
}

CAStarNode::~CAStarNode()
{
	clear();
}

/// @return the path to the goal as a list of CAStarNodes, or an empty list if no path was possible.
QList<CAStarNode*>	CAStarNode::path()
{
	QList<CAStarNode*> rc;
	clear();
	if ( seek() && !mChildren.isEmpty() )
	{
		CAStarNode* child = mChildren.first();
		while( child )
		{
			rc.append(child);
			child = child->children().isEmpty() ? NULL : child->children().first();
		}
	}
	return rc;
}

/// Seek a path to the goal.
/// @return true if we found a path.
bool CAStarNode::seek()
{
	bool found = (goalRect().contains(pos()));
	if ( !found )
	{
		instantiateNeighbors();
		close();				// this node has been explored.
		while(!mChildren.isEmpty())
		{
			CAStarNode* child = mChildren.first();
			if ( !(found = child->seek()) )
			{
				// at this point child has been fully explored with no solution.
				mChildren.takeFirst();
				delete child;
			}
		}
	}
	return found;
}

/// Return the bounding (containing) rect in grid coordinates containing the point in sceen coordinates.
/// @param pt a point in scene coordinates.
QRectF CAStarNode::gridRect(QPointF pt)
{
	double gridX = (int)(pt.x() / gridRez());
	double gridY = (int)(pt.y() / gridRez());
	QRectF rc( gridX, gridY, gridRez(), gridRez() );
	return rc;
}

/// Set the goal point and calculate the containg grid rect.
void CAStarNode::setGoal(QPointF pt)
{
	mGoalPt		= pt;
	mGoalRect	= gridRect(pt);
}


/// The initial neigbor instantiation, these become owned by this as children.
void CAStarNode::instantiateNeighbors()
{
	if ( mChildren.isEmpty() )
	{
		QPoint pt;
		for(pt.setX(-1); pt.x()<=1; pt.setX(pt.x()+1))
		{
			for(pt.setY(-1); pt.y()<=1; pt.setY(pt.y()+1))
			{
				if ( isTraversable(pt) )
				{
					CAStarNode* child = new CAStarNode(pt,this);
					Q_ASSERT( child != NULL );
					insort(child);
				}
			}
		}
	}
}

/// Determine of the potential node would be traversable
bool CAStarNode::isTraversable(QPoint &pt)
{
	bool rc = false;
	if ( bounds().contains(pt) )
	{
		// FIXME - test for collisions with objects
		rc = true;
	}
	return rc;
}

/// insert a child sorted by cost.
void CAStarNode::insort(CAStarNode *child)
{
	for(int n=0; n < mChildren.length(); n++)
	{
		CAStarNode* other = mChildren.at(n);
		if ( *child < *other )
		{
			mChildren.insert(n,child);
		}
	}
	mChildren.append(child);
}

/// Returns the sum of the absolute values of x() and y(), traditionally known as the "Manhattan length"
/// of the vector from the origin to the point.
double CAStarNode::manhattanLength(QPointF& a, QPointF& b)
{
	QPointF delta = b - a;
	return delta.manhattanLength();
}

/// Calculate the cost between two adjacent points.
/// We will assign a cost of 10 to each horizontal or vertical square moved, and a cost of 14.14 for a diagonal move.
/// We use these numbers because the actual distance to move diagonally is the square root of 2,
/// or roughly 1.414 times the cost of moving horizontally or vertically.
double CAStarNode::adjacentCost(QPointF &a, QPointF &b)
{
	double diffX = fabs(a.x()-b.x());
	double diffY = fabs(a.y()-b.y());
	double rc = ( diffX && diffY ) ? (10*1.414) : 10.0;
	return rc;
}

/// Calculate G, the movement cost to move from the starting point A
/// to a given square on the grid, following the path generated to get there.
double CAStarNode::g()
{
	if ( !mG )
	{
		mG = adjacentCost( parent()->mPos, mPos );
		if ( parent() )
		{
			mG += parent()->mG;
		}
	}
	return mG;
}

/// @brief The estimated movement cost to move from that given square on the grid to the final destination
double CAStarNode::h()
{
	if ( !mH )
	{
		mH = manhattanLength( mPos, mGoalPt ) * 10.0;
	}
	return mH;
}

/// @brief return the node to it's initial state
void CAStarNode::clear()
{
	while(mChildren.count())
	{
		CAStarNode* child = mChildren.takeFirst();
		delete child;
	}
	mOpen	= true;
	mG		= 0;
}

CAStarNode& CAStarNode::operator=(const CAStarNode& other)
{
	if (*this != other)
	{
		mPos	= other.mPos;
		mCost	= other.mCost;
	}
	return *this;
}

bool CAStarNode::operator==(const CAStarNode& other) const
{
	return mPos.x() == other.mPos.x() && mPos.y() == other.mPos.y();
}

bool CAStarNode::operator!=(const CAStarNode& other) const
{
	return !(mPos.x() == other.mPos.x() && mPos.y() == other.mPos.y());
}

bool CAStarNode::operator<(const CAStarNode& other) const
{
	return other.mCost < mCost;
}

bool CAStarNode::operator>(const CAStarNode& other) const
{
	return other.mCost > mCost;
}


