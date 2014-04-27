/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef CGSEGMENT_H
#define CGSEGMENT_H

#include <QObject>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPointF>
#include <cgsegmentroute.h>

class CPcb;
class CPcbNet;
class CPcbLayer;
class CGSegment : public CGSegmentRoute, public QGraphicsItem
{
	Q_OBJECT
	public:

		CGSegment(CPcbNet* net);
		virtual ~CGSegment();

        virtual Segment_t           segmentType() {return Segment;}
        virtual bool				isA(CGSegment::Segment_t t) {return t==Segment || CGSegmentRoute::isA(t);}

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
};

#endif // CGSEGMENT_H
