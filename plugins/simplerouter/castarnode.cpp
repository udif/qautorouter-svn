/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarnode.h"

#define inherited CAStarMarker

CAStarNode::CAStarNode(QPoint pt, QPoint parent)
: inherited(pt, CAStarMarker::Navigation)
, mParent(parent)
, mCost(0.0)
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


bool CAStarNode::operator<=(const CAStarNode& other)
{
    CAStarNode* p = (CAStarNode*)&other;
    return cost() <= p->cost();
}

bool CAStarNode::operator>=(const CAStarNode& other)
{
    CAStarNode* p = (CAStarNode*)&other;
    return cost() >= p->cost();
}


