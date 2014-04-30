/*******************************************************************************
* Copyright (C) 2014 Pike Aerospace Research Corporation                       *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*                                                                              *
*   This program is free software: you can redistribute it and/or modify       *
*   it under the terms of the GNU General Public License as published by       *
*   the Free Software Foundation, either version 3 of the License, or          *
*   (at your option) any later version.                                        *
*                                                                              *
*   This program is distributed in the hope that it will be useful,            *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU General Public License at <http://www.gnu.org/licenses/>               *
*   for more details.                                                          *
*                                                                              *
*******************************************************************************/
#include "simplerouternode.h"

SimpleRouterNode& SimpleRouterNode::operator=(const SimpleRouterNode& other)
{
    mPos = other.mPos;
    mScore = other.mScore;
    mLayer = other.mLayer;
    return *this;
}

bool SimpleRouterNode::operator==(const SimpleRouterNode& other) const
{
    return mPos.x() == other.mPos.x() && mPos.y() == other.mPos.y();
}

bool SimpleRouterNode::operator!=(const SimpleRouterNode& other) const
{
    return mPos.x() != other.mPos.x() || mPos.y() != other.mPos.y();
}

SimpleRouterNode& SimpleRouterNode::operator=(const QPointF& other)
{
    mPos = other;
    return *this;
}

bool SimpleRouterNode::operator==(const QPointF& other) const
{
    return mPos.x() == other.x() && mPos.y() == other.y();
}

bool SimpleRouterNode::operator!=(const QPointF& other) const
{
    return mPos.x() != other.x() || mPos.y() != other.y();
}

SimpleRouterNode& SimpleRouterNode::operator=(const double& other)
{
    mScore = other;
    return *this;
}

bool SimpleRouterNode::operator==(const double& other) const
{
    return mScore == other;
}

bool SimpleRouterNode::operator!=(const double& other) const
{
    return mScore != other;
}

bool SimpleRouterNode::operator>=(const double& other) const
{
    return mScore >= other;
}

bool SimpleRouterNode::operator<=(const double& other) const
{
    return mScore <= other;
}

bool SimpleRouterNode::operator>(const double& other) const
{
    return mScore > other;
}

bool SimpleRouterNode::operator<(const double& other) const
{
    return mScore < other;
}


