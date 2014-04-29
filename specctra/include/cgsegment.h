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
#ifndef CGSEGMENT_H
#define CGSEGMENT_H

#include <QObject>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPointF>

class CPcb;
class CPcbNet;
class CPcbLayer;
class CGSegment : public QObject, public QGraphicsItem
{
	Q_OBJECT
	public:

        typedef enum
        {
            Invalid=0,
            Segment,
            Padstack,
            Wire,
            Via
        } Segment_t;

        CGSegment(CPcbNet* net);
		virtual ~CGSegment();

        virtual Segment_t           segmentType() {return Segment;}
        virtual bool				isA(Segment_t t) {return t==Segment;}

		virtual void				setWidth(double w);
		virtual double				width();

        virtual void				setOrigin(QPointF pt) {mOrigin=pt;}
        virtual QPointF				origin() {return mOrigin;}
        virtual QPointF				parentOrigin();

		virtual void				setLayer(CPcbLayer* layer);
		virtual CPcbLayer*			layer();

        virtual void				setParentSegment(CGSegment* segment) {mParentSegment=segment;}
        virtual CGSegment*			parentSegment() {return mParentSegment;}

        virtual void				append(CGSegment* segment);
        virtual int					segments();
        virtual CGSegment*			segment(int idx);
        virtual int					segmentIndexOf(CGSegment* segment) {return segmentsRef().indexOf(segment);}
		virtual bool				isEmpty() {return segments()==0;}

		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
        virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

		virtual CPcbNet*			net();
		virtual bool				selected();

        virtual QPolygonF           polygon();

        virtual void                setRouted(bool routed) {mRouted=routed;}
        virtual bool                routed() {return mRouted;}

    public slots:
		virtual void				clear();

	protected:

        QList<CGSegment*>&			segmentsRef() {return mSegments;}
		CPcbNet*					mNet;

	private:
		QList<CGSegment*>			mSegments;
		double						mWidth;
		CPcbLayer*					mLayer;
		CGSegment*					mParentSegment;
        QPointF						mOrigin;
        bool                        mRouted;
};

#endif // CGSEGMENT_H
