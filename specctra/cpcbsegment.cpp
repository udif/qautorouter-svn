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
#include "cpcbsegment.h"
#include "cpcblayer.h"
#include "cpcb.h"
#include "cpcbstructure.h"
#include "cpcbboundary.h"

#define inherited CSpecctraObject

CPcbSegment::CPcbSegment(QGraphicsItem *parent)
: inherited(parent)
{
	CSpecctraObject::globalScene()->addItem(this);
}

CPcbSegment::~CPcbSegment()
{
}

bool CPcbSegment::drawable()
{
	return true;
}

CPcbClearanceClass* CPcbSegment::clearanceClass()
{
	return (CPcbClearanceClass*)child("clearance_class");
}

CPcbNet* CPcbSegment::net()
{
	return (CPcbNet*)child("net");
}

QRectF CPcbSegment::boundingRect() const
{
	CPcbSegment* me=(CPcbSegment*)this;
	QRectF rect;
	if ( me->drawable() )
	{
		me->setZValue(me->layerIndex());
		rect = me->shape().boundingRect();
	}
	else
	{
		if ( me->pcb() != NULL && me->pcb()->structure() != NULL && me->pcb()->structure()->boundary() != NULL )
		{
			QPointF topLeft = me->pcb()->structure()->boundary()->boundingRect().topLeft();
			rect.setTopLeft(topLeft);
			rect.setWidth(0);
			rect.setHeight(0);
		}
	}
	return rect;
}

void CPcbSegment::paint(QPainter* painter, const QStyleOptionGraphicsItem* /* option */, QWidget* /* widget */)
{
	if ( drawable() )
	{
		painter->setRenderHint(QPainter::Antialiasing);
		painter->scale(scale(),scale());
		painter->setPen(QPen(color(), width(), Qt::SolidLine,Qt::RoundCap));
		painter->drawPath(shape());
	}
}

