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
#include <QList>

class CPcb;
class CPcbNet;
class CPcbLayer;
class CGSegment;

class CRouteState
{
    public:
        CRouteState()
        : grid(1.0)
        , startPt(NULL)
        , goalPt(NULL)
        {}
        ~CRouteState()
        {
            while(openList.count()>0)   delete openList.takeLast();
            while(closedList.count()>0) delete closedList.takeLast();
            while(result.count()>0)     delete result.takeLast();
        }

        double              grid;
        QList<CGSegment*>   openList;
        QList<CGSegment*>   closedList;
        QList<CGSegment*>   result;
        CGSegment*          startPt;
        CGSegment*          goalPt;
};

class CGSegmentRoute : public QObject
{
	Q_OBJECT
	public:

        typedef struct
        {
            QList<CGSegment*>   openList;
            QList<CGSegment*>   closedList;
            QList<CGSegment*>   result;
            CGSegment*          startPt;
            CGSegment*          goalPt;
        } RouteState_t;

		typedef enum
		{
            SegmentRoute=0,
            Segment,
			Padstack,
			Wire,
			Via
        } Segment_t;

        CGSegmentRoute(CPcbNet* net);
        virtual ~CGSegmentRoute();

        virtual Segment_t           segmentType() {return SegmentRoute;}
        virtual bool				isA(CGSegmentRoute::Segment_t t) {return t==SegmentRoute;}
        virtual bool				isStatic();

        /* pure virtuals */
        virtual void				setWidth(double w)=0;
        virtual double				width()=0;

        virtual void				setOrigin(QPointF pt)=0;
        virtual QPointF				origin()=0;
        virtual QPointF				parentOrigin()=0;

        virtual void				setLayer(CPcbLayer* layer)=0;
        virtual CPcbLayer*			layer()=0;

        virtual void				setParentSegment(CGSegment* segment)=0;
        virtual CGSegment*			parentSegment()=0;

        virtual void				append(CGSegment* segment)=0;
        virtual int					segments()=0;
        virtual CGSegment*			segment(int idx)=0;
        virtual int					segmentIndexOf(CGSegment* segment)=0;
        virtual bool				isEmpty()=0;

        virtual CPcbNet*			net()=0;
        virtual bool				selected()=0;

        virtual QPolygonF           polygon()=0;

        /* routing / built-in path finding */
        virtual bool				routed()                {return isStatic()?true:mRouted;}
        virtual	bool				routable()              {return isA(Wire) || isA(Via);}

    public slots:
        virtual	void				route(CGSegment* goalPt=NULL, double grid=1.0); // mil?

    signals:
        void                        signalOpen(CGSegment* segment);
        void                        signalClose(CGSegment* segment);

    public slots:
		virtual void				clear();

	protected:
        void                        setRouted(bool routed);
        QList<CGSegment*>           path(CRouteState& state);
        QList<CGSegment*>           childList(CRouteState& state, CGSegment* pt=NULL);
        void                        insort(CRouteState& state, QList<CGSegment*>& list, CGSegment* node);
        double                      cost(CRouteState& state,CGSegment* pt=NULL);
        double                      manhattanLength(CRouteState& state, QPointF a, QPointF b);
        double                      adjacentCost(CRouteState& state, QPointF a, QPointF b);
        double                      g(CRouteState& state, CGSegment* pt=NULL);
        double                      h(CRouteState& state, CGSegment* pt=NULL);
        double                      cost();
        void                        open(CRouteState& state, CGSegment* pt);
        void                        close(CRouteState& state, CGSegment* pt);

	private:
		bool						mRouted;
        double                      mCost;
};

#endif // CGSEGMENTROUTE_H
