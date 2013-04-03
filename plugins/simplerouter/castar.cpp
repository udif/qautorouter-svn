/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "castar.h"
#include "castarnode.h"

#define inherited QObject

CAStar::CAStar(QList<CAStarMarker>& keepOut, QPoint startPt, QPoint goalPt)
: inherited()
, mKeepoutList(keepOut)
, mStartPt(startPt)
, mGoalPt(goalPt)
{
}

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

/// clear memory to initial state
void CAStar::clear()
{
    openList().clear();
    closedList().clear();
}

QList<CAStarNode>& CAStar::openList()
{
    return mOpenList;
}

QList<CAStarNode>& CAStar::closedList()
{
    return mClosedList;
}

/// Transfer a node to the open list.
void CAStar::open(CAStarNode& node)
{
    int idx;
    if ( (idx=closedList().indexOf(node))>= 0 )
        closedList().takeAt(idx);
    if ( (idx=openList().indexOf(node))>= 0 )
        openList().replace(idx,node);
    else
        insort(openList(),node);
}

/// Transfer a node to the closed list.
void CAStar::close(CAStarNode& node)
{
    int idx;
    if ( (idx=openList().indexOf(node))>= 0 )
        openList().takeAt(idx);
    if ( (idx=closedList().indexOf(node))>= 0 )
        closedList().replace(idx,node);
    else
        insort(closedList(),node);
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

/// Calculate the cost of this node
double CAStar::cost(CAStarNode& node)
{
    double rc = g(node) + h(node);
    return rc;
}

/// Calculate G, the movement cost to move from the starting point A
/// to this cell of the grid, following the path generated to get there.
double CAStar::g(CAStarNode& node)
{
    double rc=0.0;
    CAStarNode* parent = &node;
    while ( parent && parent->parent() )
    {
        rc += adjacentCost( parent->parent()->pos(), parent->pos() );
        parent = parent->parent();
    }
    return rc;
}

/// @brief The estimated movement cost to move from that given square on the grid to the final destination
double CAStar::h(CAStarNode& node)
{
    double rc = manhattanLength( node.pos(), mGoalPt ) * 10.0;
    return rc;
}


