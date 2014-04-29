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
#include "cpcbboundary.h"
#include "cpcbpath.h"

#define inherited CSpecctraObject

CPcbBoundary::CPcbBoundary(QGraphicsItem *parent)
: inherited(parent)
{
	CSpecctraObject::globalScene()->addItem(this);
}

CPcbBoundary::~CPcbBoundary()
{
}

/**
  * @return the class of drawable object which this is.
  */
CSpecctraObject::tDrawableClass CPcbBoundary::drawableClass()
{
	return CSpecctraObject::Border;
}

/**
  * @return the boundary polygon...
  */
CPcbPath* CPcbBoundary::path()
{
	return (CPcbPath*)child("path");
}

QRectF CPcbBoundary::boundingRect() const
{
	QRectF bounds = shape().boundingRect();
	return bounds;
}

QPainterPath CPcbBoundary::shape() const
{
	QPainterPath p;
	CPcbBoundary* me=(CPcbBoundary*)this;
	if (me->path()!=NULL)
	{
		p = me->path()->shape();
	}
	return p;
}

void CPcbBoundary::paint(QPainter *painter, const QStyleOptionGraphicsItem* /* option */, QWidget* /* widget */)
{
	QPainterPath p = shape();
	painter->setRenderHint(QPainter::Antialiasing);
	painter->scale(scale(),scale());
	painter->setPen(QPen(QColor(255, 255, 0), 10, Qt::SolidLine,Qt::FlatCap,Qt::MiterJoin));
	painter->drawPath(shape());
}

