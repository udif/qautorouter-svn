/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarnode.h"

#define inherited CAStarMarker

CAStarNode::CAStarNode(CAStarNode* parent)
: inherited(QPoint(0,0), CAStarMarker::Navigation)
, mParent(parent)
, mCost(0.0)
{
}

CAStarNode::CAStarNode(QPoint pt, CAStarNode* parent)
: inherited(pt, CAStarMarker::Navigation)
, mParent(parent)
, mCost(0.0)
{
}

CAStarNode::CAStarNode(QPoint pt, double cost, CAStarNode* parent)
: inherited(pt, CAStarMarker::Navigation)
, mParent(parent)
, mCost(cost)
{
}

CAStarNode::CAStarNode(const CAStarNode& other)
: inherited(other)
, mParent(other.mParent)
, mCost(other.mCost)
{
}

CAStarNode::~CAStarNode()
{
}

CAStarNode& CAStarNode::operator=(const CAStarNode& other)
{
    if ( this != &other)
	{
        mParent = other.mParent;
		mCost	= other.mCost;
        mPos    = other.mPos;
        mKind   = other.mKind;
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

bool CAStarNode::operator<(const CAStarNode& other)
{
	CAStarNode* p = (CAStarNode*)&other;
	return cost() < p->cost();
}

bool CAStarNode::operator>(const CAStarNode& other)
{
	CAStarNode* p = (CAStarNode*)&other;
	return cost() > p->cost();
}


