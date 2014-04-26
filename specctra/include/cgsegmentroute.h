/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef CGSEGMENTROUTE_H
#define CGSEGMENTROUTE_H

#include <QObject>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QPolygonF>
#include <QPointF>

class CPcb;
class CPcbNet;
class CPcbLayer;
class CGSegment;
class CGSegmentRoute : public QObject
{
	Q_OBJECT
	public:

		typedef enum
		{
            Segment=0,
			Padstack,
			Wire,
			Via
        } tSegmentType;

        CGSegmentRoute(CPcbNet* net);
        virtual ~CGSegment();

        virtual tSegmentType		segmentType() {return mSegmentType;}
        virtual bool				isA(CGSegment::tSegmentType t) {return t==mSegmentType || t==CGSegment::Segment;}
		virtual bool				isStatic();

		virtual void				setWidth(double w);
		virtual double				width();

		void						setOrigin(QPointF pt) {mOrigin=pt;}
		virtual QPointF				origin() {return mOrigin;}
		QPointF						parentOrigin();

		virtual void				setLayer(CPcbLayer* layer);
		virtual CPcbLayer*			layer();

		void						setParentSegment(CGSegment* segment) {mParentSegment=segment;}
		CGSegment*					parentSegment() {return mParentSegment;}

		void						append(CGSegment* segment);
		int							segments();
		CGSegment*					segment(int idx);
		int							segmentIndexOf(CGSegment* segment) {return segmentsRef().indexOf(segment);}
		virtual bool				isEmpty() {return segments()==0;}

		virtual QRectF				boundingRect() const;
		virtual QPainterPath		shape() const;
        virtual void				paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

		virtual CPcbNet*			net();
		virtual bool				selected();

        virtual QPolygonF           polygon();

        /* routing / built-in A* path finding */
        virtual bool				routed()                {return isStatic()?true:mRouted;}
        virtual	bool				routable()              {return isA(Wire) || isA(Via);}
        virtual	void				route(double grid=0.5); // mil?

public slots:
		virtual void				clear();

	protected:
        inline void                 setCost(double cost)    {mCost=cost;}
        inline double               cost()                  {return mCost;}
        virtual void                setRouted(bool routed)  {mRouted=routed;}
        double                      manhattanLength(CGSegment* a, CGSegment* b);
        double                      adjacentCost(double grid, QPointF a, QPointF b);
        double                      g(CGSegment* node,CGSegment* parent);
        double                      h(QPointF a, QPointF goal);
        double                      cost(CGSegment* node, CGSegment* parent);
        QList<CGSegment*>&          path( double grid, CGSegment& target );
        QList<CGSegment*>&			segmentsRef() {return mSegments;}
        tSegmentType                mSegmentType;
		CPcbNet*					mNet;

	private:
		QList<CGSegment*>			mSegments;
		double						mWidth;
		CPcbLayer*					mLayer;
		CGSegment*					mParentSegment;
		QPointF						mOrigin;
		bool						mRouted;
        double                      mCost;
};

#endif // CGSEGMENTROUTE_H
