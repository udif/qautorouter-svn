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
#ifndef CPCBSEGMENT_H
#define CPCBSEGMENT_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>

#include "cspecctraobject.h"

/**
  * @brief Baseclass for drawable wires, vias and the like.
  */

class CPcbNet;
class CPcbClearanceClass;
class CPcbSegment : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbSegment(QGraphicsItem *parent = 0);
		virtual ~CPcbSegment();

		virtual double					layerIndex()=0;
		virtual double					width()=0;
		virtual QColor					color()=0;
		virtual bool					drawable();
		virtual CPcbNet*				net();
		virtual CPcbClearanceClass*		clearanceClass();

		/** QGraphicsItem overrides... */
		virtual QRectF					boundingRect() const;
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
};

#endif // CPCBSEGMENT_H

