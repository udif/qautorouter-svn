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

#define inherited QObject

CGSegment::CGSegment(CPcbNet* net)
: inherited(NULL)
, mSegmentType(Segment)
, mNet(net)
, mWidth(0.0)
, mLayer(NULL)
, mParentSegment(NULL)
, mRouted(false)
, mCost(0.0)
, mGrid(0.0)
{
	CSpecctraObject::globalScene()->addItem(this);
}

CGSegment::~CGSegment()
{
	clear();
}

/**
  * @brief clear
  */
void CGSegment::clear()
{
	mSegments.clear();
}

/**
  * @return the net that this segmetn belongs to
  */
CPcbNet* CGSegment::net()
{
	if ( mNet == NULL )
	{
		if ( parentSegment() != NULL )
			mNet = parentSegment()->net();
	}
	return mNet;
}

/**
  * @return true of the net is selected.
  */
bool CGSegment::selected()
{
	if ( net() != NULL )
	{
		return net()->isSelected();
	}
	return false;
}

/**
  * @brief determine if the segment is a permanent fixture?
  */
bool CGSegment::isStatic()
{
	return isA(CGSegment::Padstack) && isA(CGSegment::Via);
}

/**
  * @brief set the segment width.
  */
void CGSegment::setWidth(double w)
{
	mWidth=w;
}

/**
  * @return the segment width.
  */
double CGSegment::width()
{
	return mWidth;
}

/**
  * @brief set the pointer to the segment layer.
  */
void CGSegment::setLayer(CPcbLayer* layer)
{
	mLayer=layer;
}

/**
  * @return the a pointer to the segment layer.
  */
CPcbLayer* CGSegment::layer()
{
	return mLayer;
}

/**
  * @brief Append a segment to the list of segments
  */
void CGSegment::append(CGSegment* segment)
{
	mSegments.append(segment);
	segment->setParentSegment(this);
}

/**
  * @brief get the number of segments attached to this segment.
  */
int CGSegment::segments()
{
	return mSegments.count();
}

/**
  * @return A segment by index
  */
CGSegment* CGSegment::segment(int idx)
{
	return mSegments.at(idx);
}

/**
  * @return A union of all attached segments.
  */
QRectF CGSegment::boundingRect() const
{
	QRectF bounds = shape().boundingRect();
	return bounds;
}

/**
  * @return the parent position point or of parent is NULL, then this position pont.
  */
QPointF CGSegment::parentOrigin()
{
	if ( parentSegment() != NULL )
	{
		return parentSegment()->origin();
	}
	return origin();
}

/**
  * @return the segment shape.
  */
QPainterPath CGSegment::shape() const
{
	CGSegment* me=(CGSegment*)this;
	QPainterPath ppath;
	ppath.moveTo(me->parentOrigin());
	ppath.lineTo(me->origin());
	return ppath;
}

void CGSegment::paint(QPainter *painter, const QStyleOptionGraphicsItem* /* option */, QWidget* /* widget */)
{
	int w=width();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->scale(scale(),scale());
	if ( !selected() )
	{
		painter->setPen(QPen(QColor(255,255,255), w<=0?3:width(), Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));
	}
	else
	{
		painter->setPen(QPen(QColor(255,255,0), w<=0?10:width(), Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));
	}
	painter->drawPath(shape());
}

/**
 * @brief Route the segment.
 */
void CGSegment::route(double grid,CGSegment* other)
{
    QList<CGSegment*> openList;
    QList<CGSegment*> closedList;
    QList<CGSegment*> result;
    if ( other )
    {
        result = path(grid,other,openList,closedList);
    }
    else
    {
        /** FIXME - itterate rat tree for loose connections */
    }
}

/**
 * @return the shape as a polygon
 */
QPolygonF CGSegment::polygon()
{
    QPainterPath path = shape();
    QPolygonF polygon = path.toFillPolygon();
    return polygon;
}

/**
 * @brief Find best path from this segment to target segment using a specified seach grid.
 * @param grid The search grid expressed in mils.
 * @param target The taget CGSegment, meaning the end connection point of the path.
 * @return A list of segments making up the path.
 */
QList<CGSegment*> CGSegment::path(double grid, CGSegment* other, QList<CGSegment*> openList, QList<CGSegment*> closedList )
{

}

/**
 * @brief Insert a node into the list maintaining a sort based on cost.
 * @param list List of nodes sorted by cost.
 * @param node The new node to insert into the list.
 */
void CGSegment::insort(QList<CGSegment*>& list, CGSegment* node)
{
    int idx = list.indexOf(node);
    if ( idx < 0 ) // insorted already?
    {
        int len = list.length();
        for(int n=0; n < len; n++)
        {
            CAStarNode* other = list[n];
            if ( node->cost() < other.cost() )
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
double CGSegment::cost()
{
    double rc = g() + h();
    return rc;
}

/**
 * @brief Calculate G, the movement cost to move from the starting point to this point in the grid
 *        following the generated path to get there.
 * @param node
 * @param parent
 * @return
 */
double CGSegment::g()
{
    double rc=adjacentCost(pos(),other->pos());
    CGSegment* parent = other->parent();

    while( !isEmpty( node.parent() ) )
    {
        CAStarNode other(node.parent());
        rc += adjacentCost( other.pos(), node.pos() );
        node = other;
    }
    return rc;
}

/**
 * @param goal The final destination
 * @return The estimated movement cost to move from that given square on the grid to the final destination
 */
double CGSegment::h(QPointF a, QPointF goal)
{
    double rc = manhattanLength( a.pos(), goal.pos() ) * grid(); // 10.0??
    return rc;
}

/**
 * @param a Point A
 * @param b Point B
 * @return the sum of the absolute values of x() and y(), traditionally known as the "Manhattan length"
 *         of the vector from the origin to the point.
 */
double CGSegment::manhattanLength(QPointF a, QPointF b)
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
double CGSegment::adjacentCost(double grid, QPointF a, QPointF b)
{
    double diffX = abs(a.x()-b.x());
    double diffY = abs(a.y()-b.y());
    double rc = ( diffX && diffY ) ? 1.414*grid() : grid();
    return rc;
}

