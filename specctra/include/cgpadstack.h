/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
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
        virtual bool				isA(CGSegment::Segment_t t) {t==Padstack || CGSegment::isA(t);}

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
