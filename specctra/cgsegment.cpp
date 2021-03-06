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
#include <cgsegment.h>
#include <cspecctraobject.h>
#include <cpcb.h>
#include <cpcbnetwork.h>
#include <cspecctraobject.h>
#include <cpcbnet.h>

#include <QPainter>

#define inherited QObject

CGSegment::CGSegment(CPcbNet* net)
: inherited()
, mNet(net)
, mWidth(0.0)
, mLayer(NULL)
, mParentSegment(NULL)
, mRouted(false)
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
 * @return the shape as a polygon
 */
QPolygonF CGSegment::polygon()
{
    QPainterPath path = shape();
    QPolygonF polygon = path.toFillPolygon();
    return polygon;
}


