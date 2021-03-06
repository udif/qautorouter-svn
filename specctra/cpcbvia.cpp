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
#include "cpcbvia.h"
#include "cpcb.h"
#include "cpcblibrary.h"
#include "cpcbpadstack.h"
#include "cpcbshape.h"

#include <stdio.h>

#define inherited CPcbSegment

CPcbVia::CPcbVia(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbVia::~CPcbVia()
{
}

/**
  * @return the class of drawable object which this is.
  */
CSpecctraObject::tDrawableClass CPcbVia::drawableClass()
{
	return CSpecctraObject::Via;
}

/**
  * @return a layer index used for Z-axis layering.
  */
double CPcbVia::layerIndex()
{
	return 100;
}

bool CPcbVia::drawable()
{
	if ( properties().count() >= 3 && parentObject() != NULL ) // do we have coordinates?
		if ( parentObject()->objectClass() == "wiring" )
			return true;
	return false;
}

QPointF CPcbVia::center()
{
	QPointF pt;
	if ( drawable() )
		pt = QPointF(properties()[1].toDouble(),properties()[2].toDouble());
	return pt;
}

double CPcbVia::width()
{
	return 1.0;
}

QColor CPcbVia::color()
{
	/** FIXME this should combine the colors of the layers of the padstack */
	QColor c(207, 181, 59);
	return c;
}

/**
  * @return a pointer to the padstack object
  */
CPcbPadstack* CPcbVia::padstack()
{
	CPcbPadstack* ps=NULL;
	if ( pcb() != NULL && pcb()->library() != NULL && properties().count() )
	{
		ps = pcb()->library()->padstack(properties().at(0));
	}
	return ps;
}

QPainterPath CPcbVia::shape() const
{
	CPcbVia* me=(CPcbVia*)this;
	QPainterPath ppath;
	if ( me->drawable() )
	{
		if ( me->padstack() != NULL )
		{
			for(int n=0; n < me->padstack()->shapes(); n++)
			{
				QPainterPath other = me->padstack()->shape(n)->shape();
				ppath.addPath(other);
			}
		}
		ppath.translate(me->center());
	}
	return ppath;
}

void CPcbVia::paint(QPainter* painter, const QStyleOptionGraphicsItem* /* option */, QWidget* /* widget */)
{
	if ( drawable() )
	{
		QPainterPath ppath = shape();
		painter->setRenderHint(QPainter::Antialiasing);
		painter->scale(scale(),scale());
		ppath.setFillRule(Qt::WindingFill);
		painter->setPen(QPen(color(), width(), Qt::SolidLine,Qt::RoundCap));
		painter->drawPath(ppath);
		painter->fillPath(ppath,color());
	}
}

