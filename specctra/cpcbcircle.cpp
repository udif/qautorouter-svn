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
#include "cpcbcircle.h"
#include <QPointF>
#include <math.h>

#define inherited CSpecctraObject

CPcbCircle::CPcbCircle(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbCircle::~CPcbCircle()
{
}

double CPcbCircle::radius()
{
	return properties().at(1).toDouble()/2.0;
}

QString CPcbCircle::layer()
{
	return properties().at(0);
}

QPainterPath CPcbCircle::path()
{
	QPainterPath ppath;
	QPoint topLeft(-radius(),-radius());
	QPoint bottomRight(radius(),radius());
	ppath.addEllipse(QRectF(topLeft,bottomRight));
	return ppath.simplified();
}
