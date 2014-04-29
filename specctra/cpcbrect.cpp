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
#include "cpcbrect.h"

#define inherited CSpecctraObject

CPcbRect::CPcbRect(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbRect::~CPcbRect()
{
}

QRectF CPcbRect::rect()
{
	QRectF r(QPointF(properties().at(1).toDouble(),properties().at(2).toDouble()),QPointF(properties().at(3).toDouble(),properties().at(4).toDouble()));
	return r;
}

QString CPcbRect::layer()
{
	return properties().at(0);
}

/**
  * @return a QPainterPath to draw the shape
  */
QPainterPath CPcbRect::path()
{
	QRectF r = rect();
	QPainterPath ppath;
	ppath.addRect(r);
	return ppath;
}
