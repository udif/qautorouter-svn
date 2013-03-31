/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarnode.h"

QRect	CAStarNode::mBounds;
QPoint	CAStarNode::mStart;
QPoint	CAStarNode::mGoal;

CAStarNode::CAStarNode(CAStarNode* parent)
: mParent(parent)
, mCost(0)
, mOpen(true)
, mG(0)
, mH(0)
{
}

CAStarNode::CAStarNode(QPoint pt, CAStarNode* parent)
: mParent(parent)
, mPos(pt)
, mCost(0)
, mOpen(true)
, mG(0)
, mH(0)
{
}

CAStarNode::CAStarNode(QPoint pt, int cost, CAStarNode* parent)
: mParent(parent)
, mPos(pt)
, mCost(cost)
, mOpen(true)
, mG(0)
, mH(0)
{
}

CAStarNode::CAStarNode(const CAStarNode& other)
: mParent(other.mParent)
, mPos(other.mPos)
, mCost(other.mCost)
, mOpen(true)
, mG(0)
, mH(0)
{
}

CAStarNode::~CAStarNode()
{
	clear();
}

/// Seek a path to the goal.
/// @return true if we found a path.
bool CAStarNode::seek()
{
	bool found = (goal()==pos());
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
int CAStarNode::manhattanLength(QPoint& a, QPoint& b)
{
	QPoint delta = b - a;
	return delta.manhattanLength();
}

/// Calculate the cost between two adjacent points.
/// We will assign a cost of 10 to each horizontal or vertical square moved, and a cost of 14 for a diagonal move.
/// We use these numbers because the actual distance to move diagonally is the square root of 2 (don’t be scared),
/// or roughly 1.414 times the cost of moving horizontally or vertically. We use 10 and 14 for simplicity’s sake.
int CAStarNode::adjacentCost(QPoint &a, QPoint &b)
{
	int diffX = abs(a.x()-b.x());
	int diffY = abs(a.y()-b.y());
	int rc = ( diffX && diffY ) ? 14 : 10;
	return rc;
}

/// Calculate G, the movement cost to move from the starting point A
/// to a given square on the grid, following the path generated to get there.
int CAStarNode::g()
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
int CAStarNode::h()
{
	if ( !mH )
	{
		mH = manhattanLength( mPos, mGoal ) * 10;
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


