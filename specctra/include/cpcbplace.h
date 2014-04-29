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
#ifndef CPCBPLACE_H
#define CPCBPLACE_H

#include <QObject>
#include <QString>
#include <QPolygonF>
#include <QMap>

#include "cspecctraobject.h"
#include "cgpadstack.h"

class CPcbPin;
class CPcbPlace : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbPlace(QGraphicsItem *parent = 0);
		virtual ~CPcbPlace();

		virtual CSpecctraObject::tDrawableClass			drawableClass();

		QString							unit();
		QPointF							pos();
		QString							side();
		CPcbPin*						pin(QString ref);
		int								pads();
		CGPadstack*						pad(int idx);
		CGPadstack*						pad(QString ref);
        bool                            contains(CGSegment* padstack);
		double							rotation();
		QPainterPath&					outlineShape();
		virtual QRectF					boundingRect() const;
		virtual QPainterPath			shape() const;
		virtual void					paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

        QPointF                         centre();

        /* gEDA export methods */
        virtual QString					gedaObjectClass();
        virtual QStringList				gedaProperties();
        virtual QList<CSpecctraObject*>	gedaChildren();

	protected:
		void							createPadstacks();
	private:
		bool							mPadstacksCreated;
		QPainterPath					mOutlineShape;
		QList<CGPadstack*>				mPads;
};

#endif // CPCBPLACE_H

