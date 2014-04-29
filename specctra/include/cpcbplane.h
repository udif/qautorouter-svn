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
#ifndef CPCBPLANE_H
#define CPCBPLANE_H

#include <QObject>

#include "cpcbsegment.h"

class CPcbNet;
class CPcbPath;
class CPcbLayer;
class CPcbPlane : public CPcbSegment
{
	Q_OBJECT
	public:
		CPcbPlane(QGraphicsItem *parent = 0);
		virtual ~CPcbPlane();

		virtual CSpecctraObject::tDrawableClass			drawableClass();

		virtual double					layerIndex();
		virtual double					width();
		virtual QColor					color();
		virtual bool					drawable();
		virtual CPcbNet*				net();
		virtual QString					netRef();
		virtual QString					layerRef();
		virtual CPcbLayer*				layer();
		virtual CPcbPath*				path();

		/** QGraphicsItem overrides... */
		virtual QPainterPath			shape() const;
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

#endif // CPCBPLANE_H

