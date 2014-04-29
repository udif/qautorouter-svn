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
#ifndef CPCBVIA_H
#define CPCBVIA_H

#include <QObject>
#include <QGraphicsItem>

#include "cpcbsegment.h"

class CPcbPadstack;
class CPcbVia : public CPcbSegment
{
	Q_OBJECT
	public:
		CPcbVia(QGraphicsItem *parent = 0);
		virtual ~CPcbVia();

		virtual CSpecctraObject::tDrawableClass			drawableClass();

		virtual double					layerIndex();
		virtual bool					drawable();
		virtual QPointF					center();
		virtual double					width();
		virtual QColor					color();
		virtual CPcbPadstack*			padstack();

		/** QGraphicsItem overrides... */
		virtual QPainterPath			shape() const;
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

#endif // CPCBVIA_H

