/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#include "cgsegment.h"
#include "cspecctraobject.h"
#include "cpcb.h"
#include "cpcbnetwork.h"
#include "cspecctraobject.h"
#include "cpcbnet.h"

#include <QPainter>
#include <QEventLoop>

#define inherited QObject

CGSegmentRoute::CGSegmentRoute()
: inherited(NULL)
, mRouted(false)
, mCost(0.0)
{
}

CGSegmentRoute::~CGSegmentRoute()
{
	clear();
}

/**
  * @brief clear
  */
void CGSegmentRoute::clear()
{
}

/**
  * @brief determine if the segment is a permanent fixture?
  */
bool CGSegmentRoute::isStatic()
{
    return isA(CGSegmentRoute::Padstack) && !isA(CGSegmentRoute::Via);
}

/**
 * @brief Set the segment to the routed state.
 * @param routed Boolean
 */
void CGSegmentRoute::setRouted(bool routed)
{
    mRouted=routed;
}

/**
 * @brief Route the segment.
 */
void CGSegmentRoute::route(CGSegment* goalPt, double grid)
{
    CRouteState state;
    state.goalPt = goalPt;
    state.startPt = qobject_cast<CGSegment*>(this);
    state.grid = grid;
    if ( goalPt )
    {
        state.result = path(state);
    }
    else
    {
        /** FIXME - itterate rat tree for loose connections */
    }
}

/**
 * @brief Find best path from this segment to target segment using a specified seach grid.
 * @param grid The search grid expressed in mils.
 * @param target The taget CGSegment, meaning the end connection point of the path.
 * @return A list of segments making up the path.
 */
QList<CGSegment*> CGSegmentRoute::path(CRouteState& state)
{
    QList<CGSegment*> rc;
    CGSegment* node = NULL;
    QEventLoop eventLoop;
    int idx=0;

    insort(state,state.openList,state.startPt);             // Initialize the open list with that starting point.

    for( node=state.startPt; !state.openList.isEmpty() && (node = state.openList.takeFirst()) != state.goalPt; )
    {
        eventLoop.processEvents();
        QList<CGSegment*> children = childList(state,node);
        for(int n=0; n < children.count(); n++)
        {
            CGSegment* child = children[n];
            int oIdx = state.openList.indexOf(child);       // Child node already in the open list?
            if ( oIdx >=0 )
            {
                CGSegment* other = state.openList[oIdx];    // The existing node is better?
                if ( other->cost() <= child->cost() )
                    continue;
            }
            int cIdx = state.closedList.indexOf(child);     // Child node already in the closed list?
            if ( cIdx >= 0 )
            {
                CGSegment* other = state.closedList[cIdx];  // The existing node is better?
                if ( other->cost() <= child->cost() )
                    continue;
            }
            if ( oIdx >= 0 )                                // Remove child from open and closed lists
                state.openList.takeAt(oIdx);
            if ( cIdx >= 0 )
                state.closedList.takeAt(cIdx);
            open(state,child);                              // Add child to open list
        }
        close(state,node);
    }

    // follow parent nodes from goal back to start
    do
    {
        CGSegment* other = node->parentSegment();
        rc.append(node);
        if ( ( idx = state.closedList.indexOf( other ) ) >= 0 )
            other = state.closedList.takeAt(idx);
        else
        if ( ( idx = state.openList.indexOf( other ) ) >= 0 )
            other = state.openList.takeAt(idx);
        else
            break;
        node = other;
    } while( node != state.startPt );
    return rc;
}

/**
 * @brief Transfer a node to the open list.
 */
void CGSegmentRoute::open(CRouteState& state, CGSegment* pt)
{
    if (!pt)
        pt = qobject_cast<CGSegment*>(this);
    insort(state,state.openList,pt);
    emit signalOpen(pt);
}

/**
 * @brief Transfer a node to the closed list.
 */
void CGSegmentRoute::close(CRouteState& state, CGSegment* pt)
{
    if (!pt)
        pt = qobject_cast<CGSegment*>(this);
    insort(state,state.closedList,pt);
    emit signalClose(pt);
}

/**
 * @brief Create a child list to explore from neighbours.
 * @param state The current state of the path finding process.
 * @param pt If not NULL, then use the segment at this point or else if NULL, then use this.
 * @return A list of neighbours to explore.
 */
QList<CGSegment*> CGSegmentRoute::childList(CRouteState& state, CGSegment* pt)
{
    QList<CGSegment*> rc;
    if (!pt)
        pt = qobject_cast<CGSegment*>(this);
    for(int x=-state.grid; x<=state.grid; x++)
    {
        for(int y=-state.grid; y<=state.grid; y++)
        {
            CGSegment* child = new CGSegment(state.startPt->net());
            child->setPos(QPointF(pt->pos().x()+x,pt->pos().y()+y));
            child->setCost( child->cost( state ) );
            rc.append(child);
        }
    }
    return rc;
}

/**
 * @brief Insert a node into the list maintaining a sort based on cost.
 * @param list List of nodes sorted by cost.
 * @param node The new node to insert into the list.
 */
void CGSegmentRoute::insort(CRouteState& state, QList<CGSegment*>& list, CGSegment* node)
{
    int idx = list.indexOf(node);
    if ( idx < 0 ) // insorted already?
    {
        int len = list.length();
        for(int n=0; n < len; n++)
        {
            CGSegment* other = list[n];
            if ( node->cost(state) < other->cost(state) )
            {
                list.insert(n,node);
                break;
            }
        }
        if ( len == list.length() ) // no insert yet?
            list.append(node);
    }
}

/**
 * @brief Calculate the cost of this node based on the g() and h() functions. Cost in terms of efficiency.
 * @param node The
 * @param parent
 * @return
 */
double CGSegmentRoute::cost(CRouteState& state, CGSegment* pt)
{
    if (!pt)
        pt = qobject_cast<CGSegment*>(this);
    mCost = g(state,pt) + h(state,pt);
    return cost();
}

/**
 * @brief Calculate the cost of this node based on the g() and h() functions. Cost in terms of efficiency.
 * @param node The
 * @param parent
 * @return
 */
double CGSegmentRoute::cost()
{
    return mCost;
}

void CGSegmentRoute::setCost(double cost)
{
    mCost = cost;
}

/**
 * @brief Calculate G, the movement cost to move from the starting point to this point in the grid
 *        following the generated path to get there.
 * @param node
 * @param parent
 * @return
 */
double CGSegmentRoute::g(CRouteState& state, CGSegment* pt)
{
    if ( !pt )
        pt = qobject_cast<CGSegment*>(this);
    double rc=adjacentCost(state,state.startPt->pos(),pt->pos());
    for( ; pt && pt != state.startPt; pt = pt->parentSegment() )
        rc += adjacentCost( state, state.startPt->pos(), pt->pos() );
    return rc;
}

/**
 * @param goal The final destination
 * @return The estimated movement cost to move from that given square on the grid to the final destination
 */
double CGSegmentRoute::h(CRouteState& state, CGSegment* pt)
{
    if ( !pt )
        pt = qobject_cast<CGSegment*>(this);
    double rc = manhattanLength( state, pt->pos(), state.goalPt->pos() ) * state.grid; // 10.0??
    return rc;
}

/**
 * @param a Point A
 * @param b Point B
 * @return the sum of the absolute values of x() and y(), traditionally known as the "Manhattan length"
 *         of the vector from the origin to the point.
 */
double CGSegmentRoute::manhattanLength(CRouteState& state, QPointF a, QPointF b)
{
    QPointF delta = (b - a);
    return delta.manhattanLength();
}

/**
 * @brief Calculate the cost between two adjacent points. We will assign a cost of 1 to each horizontal or vertical square moved, and a cost of 14.14 for a diagonal move.
 *        We use these numbers because the actual distance to move diagonally is the square root of 2, or roughly 1.414 times the cost of moving horizontally or vertically.
 * @param grid The grid resolution
 * @param a Point A
 * @param b Point B
 * @return The calculated cost between the two points.
 */
double CGSegmentRoute::adjacentCost(CRouteState& state, QPointF a, QPointF b)
{
    double diffX = abs(a.x()-b.x());
    double diffY = abs(a.y()-b.y());
    double rc = ( diffX && diffY ) ? 1.414*state.grid : state.grid;
    return rc;
}

