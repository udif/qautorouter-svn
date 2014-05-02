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

SimpleRouterNode::SimpleRouterNode(SimpleRouterNode* parent,QPointF origin)
: mParent(parent)
, mOrigin(origin)
, mScore(0.0)
, mLayer(0)
{
}

SimpleRouterNode::SimpleRouterNode(QPointF origin,int layer)
: mParent(NULL)
, mOrigin(origin)
, mScore(0.0)
, mLayer(layer)
{
}

SimpleRouterNode::SimpleRouterNode(const SimpleRouterNode& other)
: mParent(other.mParent)
, mOrigin(other.mOrigin)
, mScore(other.mScore)
, mLayer(other.mLayer)
{
}


SimpleRouterNode& SimpleRouterNode::operator=(const SimpleRouterNode& other)
{
    if ( &other != this )
    {
        mParent = other.mParent;
        mOrigin = other.mOrigin;
        mScore = other.mScore;
        mLayer = other.mLayer;
    }
    return *this;
}

bool SimpleRouterNode::operator==(const SimpleRouterNode& other) const
{
    return mOrigin.x() == other.mOrigin.x() && mOrigin.y() == other.mOrigin.y();
}

bool SimpleRouterNode::operator!=(const SimpleRouterNode& other) const
{
    return mOrigin.x() != other.mOrigin.x() || mOrigin.y() != other.mOrigin.y();
}

SimpleRouterNode& SimpleRouterNode::operator=(const QPointF& other)
{
    mOrigin = other;
    return *this;
}

bool SimpleRouterNode::operator==(const QPointF& other) const
{
    return mOrigin.x() == other.x() && mOrigin.y() == other.y();
}

bool SimpleRouterNode::operator!=(const QPointF& other) const
{
    return mOrigin.x() != other.x() || mOrigin.y() != other.y();
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

bool SimpleRouterNode::operator>=(const SimpleRouterNode& other) const
{
    return mScore >= other.mScore;
}

bool SimpleRouterNode::operator<=(const SimpleRouterNode& other) const
{
    return mScore <= other.mScore;
}

bool SimpleRouterNode::operator>(const SimpleRouterNode& other) const
{
    return mScore > other.mScore;
}

bool SimpleRouterNode::operator<(const SimpleRouterNode& other) const
{
    return mScore < other.mScore;
}


