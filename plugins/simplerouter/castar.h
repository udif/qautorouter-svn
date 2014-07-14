/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTAR_H
#define _CASTAR_H

#include "castarmarker.h"
#include "castarnode.h"

#include <QObject>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPoint>
#include <QRect>
#include <QPointF>
#include <QRectF>
#include <QMap>
#include <QRegion>

class CGPcb;
class CAStarNode;
class CAStar : public QObject
{
	Q_OBJECT
	/// @brief The A* algorithm
	public:

		CAStar();
		CAStar( QList<CAStarMarker>& keepOut, QPoint startPt, QPoint goalPt );
		CAStar(const CAStar& other);
		virtual ~CAStar();

		QList<CAStarNode>           path( QList<CAStarMarker>& keepOut, QPoint startPt, QPoint goalPt );
		QList<CAStarNode>           path();
		void                        setKeepOut(QList<CAStarMarker>& keepOut) {mKeepoutList=keepOut;}
		void                        setStart(QPoint pt) {mStartPt=pt;}
		void                        setGoal(QPoint pt) {mGoalPt=pt;}
		QList<CAStarMarker>&        keepOutList() {return mKeepoutList;}
		QPoint                      start() {return mStartPt;}
		QPoint                      goal()  {return mGoalPt;}

	signals:
		void						signalOpen(QPoint pt);
		void						signalClose(QPoint pt);

	protected:

		void                        clear();
		bool                        isEmpty(QPoint pt);
		void                        insort(QList<CAStarNode>& list,CAStarNode& node);
		QList<CAStarNode>           childList(CAStarNode& node);
		int                         nodeIndex(QList<CAStarNode>& list,QPoint pt);
		void                        open(CAStarNode& node);
		void                        close(CAStarNode& node);
		double                      manhattanLength(QPoint a, QPoint b);
		double                      adjacentCost(QPoint a, QPoint b);
		double                      g(CAStarNode node,CAStarNode parent);
		double                      h(CAStarNode node);
		double                      cost(CAStarNode node, CAStarNode parent);

	private:

		QList<CAStarMarker>         mKeepoutList;
		QPoint                      mStartPt;
		QPoint                      mGoalPt;
		QList<CAStarNode>           mOpenList;
		QList<CAStarNode>           mClosedList;
};


#endif // _CAStar_H
