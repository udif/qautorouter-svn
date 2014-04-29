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
#ifndef CPCBNET_H
#define CPCBNET_H

#include "cspecctraobject.h"

#include "cutil.h"
#include "cgwire.h"

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>
#include <QPainterPath>
#include <QList>

class CPcbPin;
class CPcbClass;
class CGPadstack;
class CGWire;
class CPcbNet : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbNet(QGraphicsItem *parent = 0);
		virtual ~CPcbNet();

		virtual QString				name();
		virtual QString				description();

		QStringList&				pinRefs();

		int							padstacks();
		CGPadstack*					padstack(int idx);
		CGPadstack*					padstack(QString ref);
		QList<CGPadstack*>&			padstacksRef();
		CGWire&						wire();

		void						sort();
		void						dumpLength();

		void						setWidth(double w) {mWidth=w;}
        double						width();
		CPcbClass*					netClass();
		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
        virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

        bool						routed();

    protected:
		CGPadstack*					closest(int n,QPointF pt);
		CGPadstack*					farthest(int n,QPointF pt);
		void						swap(CGPadstack* p1,CGPadstack* p2);

	private:
		double						mWidth;			/* trace width */
		QStringList					mPinRefs;
		QList<CGPadstack*>			mPadstacks;		/* pin padstacks */
		CGWire*						mWire;
};

#endif // CPCBNET_H

