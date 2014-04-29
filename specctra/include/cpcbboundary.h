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
#ifndef CPCBOUNDARY_H
#define CPCBOUNDARY_H


#include "cspecctraobject.h"

#include <QObject>
#include <QString>

class CPcbPath;
class CPcbBoundary : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbBoundary(QGraphicsItem *parent = 0);
		virtual ~CPcbBoundary();

		virtual CSpecctraObject::tDrawableClass			drawableClass();

		CPcbPath*					path();
		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
		virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

};

#endif // CPCBLAY_H

