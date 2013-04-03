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

/// seek the path.
QList<CAStarNode> CAStar::path()
{
    int idx;
    QList<CAStarNode> rc;
    CAStarNode node(mStartPt);
    insort(mOpenList,node);
    while(!mOpenList.isEmpty() && (node = mOpenList.takeFirst()) != mGoalPt )
    {
        node = mOpenList.takeFirst();
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
        rc.append(node);
        if ( ( idx = mClosedList.indexOf( node.parent() ) ) >= 0 )
            node = mClosedList[idx];
        else
        if ( ( idx = mOpenList.indexOf( node.parent() ) ) >= 0 )
            node = mOpenList[idx];
        else
            break;
    } while( !isEmpty(node.pos()) );
    return rc;
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

// create a child list
QList<CAStarNode> CAStar::childList(CAStarNode& node)
{
    QList<CAStarNode> rc;
    for(int x=-1; x<=1; x++)
    {
        for(int y=-1; y<=1; y++)
        {
            CAStarNode child(QPoint(x,y),node.pos());
            if ( mKeepoutList.indexOf(child) < 0 )
            {
                child.setCost( cost( child ) );
                rc.append(child);
            }
        }
    }
    return rc;
}

// return the index of a node based on a point
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
    while( !isEmpty( node.parent() ) )
    {
        int idx;
        CAStarNode parent;
        if ( ( idx = mClosedList.indexOf( node.parent() ) ) >= 0 )
            parent = mClosedList[idx];
        else
        if ( ( idx = mOpenList.indexOf( node.parent() ) ) >= 0 )
            parent = mOpenList[idx];
        rc += adjacentCost( parent.pos(), node.pos() );
        node = parent;
    }
    return rc;
}

/// @brief The estimated movement cost to move from that given square on the grid to the final destination
double CAStar::h(CAStarNode& node)
{
    double rc = manhattanLength( node.pos(), mGoalPt ) * 10.0;
    return rc;
}

/// Is the point empty - unset?
bool CAStar::isEmpty(QPoint pt)
{
    return ( pt.x() == EMPTY_X && pt.y() == EMPTY_Y );
}
