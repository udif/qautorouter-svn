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
#ifndef CGPAD_H
#define CGPAD_H

#include <QObject>
#include <QPainterPath>
#include <QString>
#include <QGraphicsItem>

class CPcb;
class CGPadstack;
class CPcbLayer;
class CGPad : public QObject, public QGraphicsItem
{
	Q_OBJECT
	public:
		explicit CGPad(CGPadstack* padstack, QPainterPath shape, QString layer, QObject *parent = 0);
        virtual ~CGPad();

        CGPadstack*					padstack() {return mPadstack;}
		CPcb*						pcb();
		QString&					layer() {return mLayer;}
		QString						pinRef();
		QPointF						pos();
		QColor						color();
		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
		virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

	private:
		CGPadstack*					mPadstack;
		QPainterPath				mShape;
		QString						mLayer;
		QRectF						mBoundingRect;
		CPcbLayer*					mLayerObject;
};

#endif // CGPAD_H
