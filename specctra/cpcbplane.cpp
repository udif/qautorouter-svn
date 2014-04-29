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
#include "cpcbplane.h"
#include "cpcb.h"
#include "cpcbstructure.h"
#include "cpcblayer.h"
#include "cpcbpath.h"
#include "cpcbnetwork.h"
#include "cpcbnet.h"

#define inherited CPcbSegment

CPcbPlane::CPcbPlane(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbPlane::~CPcbPlane()
{
}

/**
  * @return the class of drawable object which this is.
  */
CSpecctraObject::tDrawableClass CPcbPlane::drawableClass()
{
	return CSpecctraObject::Plane;
}

bool CPcbPlane::drawable()
{
	return true;
}

/**
  * @return a layer index used for Z-axis layering.
  */
double CPcbPlane::layerIndex()
{
	if ( pcb() != NULL && pcb()->structure() != NULL )
	{
		CPcbStructure* structure =  pcb()->structure();
		int layers =structure->layers();
		return layers-layer()->index();
	}
	return 0;
}

/**
  * @return the width of the wire.
  */
double CPcbPlane::width()
{
	return 1;
}

QString CPcbPlane::layerRef()
{
	QString rc;
	if ( path() != NULL )
		rc = path()->layer();
	return rc;
}

CPcbLayer* CPcbPlane::layer()
{
	if ( pcb() != NULL && pcb()->structure() != NULL )
		return pcb()->structure()->layer(layerRef());
	return NULL;
}

QColor CPcbPlane::color()
{
	QColor c(0,255,0);
	if ( layer() != NULL )
		c = layer()->color();
	return c;
}

CPcbNet* CPcbPlane::net()
{
	return pcb()->network()->net(netRef());
}

QString CPcbPlane::netRef()
{
	return properties()[0];
}

CPcbPath* CPcbPlane::path()
{
	return (CPcbPath*)child("path");
}

QPainterPath CPcbPlane::shape() const
{
	CPcbPlane* me=(CPcbPlane*)this;
	QPainterPath ppath;
	if ( me->path() != NULL )
	{
		ppath = me->path()->shape();
	}
	return ppath;
}

void CPcbPlane::paint(QPainter* painter, const QStyleOptionGraphicsItem* /* option */, QWidget* /* widget */)
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
