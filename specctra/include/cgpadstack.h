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
#ifndef CGPADSTACK_H
#define CGPADSTACK_H

#include <QObject>
#include <QPainterPath>
#include <QString>
#include <QGraphicsItem>
#include <QMap>

#include "cgsegment.h"
#include "cgpad.h"

class CPcb;
class CPcbPlace;
class CPcbNet;
class CGPadstack : public CGSegment
{
	Q_OBJECT
	public:
		CGPadstack(CPcbNet* net,CPcbPlace* place=NULL,QString pinRef=QString(),QObject *parent = 0);
        CGPadstack(const CGPadstack& other);
        virtual ~CGPadstack();

        virtual Segment_t           segmentType() {return Padstack;}
        virtual bool				isA(CGSegment::Segment_t t) {return t==Padstack || CGSegment::isA(t);}

		void						addPad(CGPad* pad);
		CPcbPlace*					place();
		CPcb*						pcb();
		CGPad*						pad(QString layer);
		QStringList					layers();
		QString&					pinRef();
		QString&					unitRef();
		virtual QPointF				origin();

		static CGPadstack*			padstack(QString& unitRef);
		static QMap<QString,CGPadstack*> padstacks() {return mGPadstacks;}

        virtual QRectF				boundingRect() const;
        virtual QPainterPath		shape() const;

	private:
		static QMap<QString,CGPadstack*> mGPadstacks;

		CPcbPlace*					mPlace;
		QString						mPinRef;
		QString						mUnitRef;
		QMap<QString,CGPad*>		mPads;

};

#endif // CGPADSTACK_H
