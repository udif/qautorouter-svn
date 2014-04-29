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
#ifndef CPCBWIRE_H
#define CPCBWIRE_H

#include "cpcbsegment.h"

#include <QPointF>
#include <QPainterPath>
#include <QWidget>

class CPcbNet;
class CPcbClearanceClass;
class CPcbPath;
class CPcbLayer;
class CPcbWire : public CPcbSegment
{
	Q_OBJECT
	public:
		CPcbWire(QGraphicsItem *parent = 0);
		virtual ~CPcbWire();

		virtual CSpecctraObject::tDrawableClass			drawableClass();

		virtual double					layerIndex();
		virtual bool					drawable();
		virtual double					width();
		virtual QColor					color();
		virtual QString					layerRef();
		virtual CPcbLayer*				layer();
		virtual CPcbPath*				path();

		/** QGraphicsItem overrides... */
		virtual QPainterPath			shape() const;
};

#endif // CPCBWIRE_H

