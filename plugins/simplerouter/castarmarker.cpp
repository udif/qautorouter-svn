/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castarmarker.h"

CAStarMarker::CAStarMarker()
: mKind(Barrier)
{
}

CAStarMarker::CAStarMarker(QPoint pt, tKind kind)
: mPos(pt)
, mKind(kind)
{
}

CAStarMarker::CAStarMarker(const CAStarMarker& other)
: mPos(other.mPos)
, mKind(other.mKind)
{
}

CAStarMarker::~CAStarMarker()
{
}

CAStarMarker& CAStarMarker::operator=(const CAStarMarker& other)
{
    if ( this != &other)
	{
        mPos    = other.mPos;
        mKind	= other.mKind;
	}
	return *this;
}

bool CAStarMarker::operator==(const CAStarMarker& other) const
{
    return mPos.x() == other.mPos.x() && mPos.y() == other.mPos.y();
}

bool CAStarMarker::operator!=(const CAStarMarker& other) const
{
    return mPos.x() != other.mPos.x() || mPos.y() != other.mPos.y();
}


bool CAStarMarker::operator==(const QPoint& other) const
{
    return mPos.x() == other.x() && mPos.y() == other.y();
}

bool CAStarMarker::operator!=(const QPoint& other) const
{
    return mPos.x() != other.x() || mPos.y() != other.y();
}


