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
#ifndef SIMPLEROUTER_H
#define SIMPLEROUTER_H

#include <QString>
#include <QDateTime>
#include <QList>
#include <QRectF>
#include <QStack>
#include <QMap>
#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <cplugininterface.h>
#include <simplerouternode.h>

class CPcb;
class CPcbNet;
class CGPadstack;
class SimpleRouter : public QObject, public CPluginInterface
 {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pikeaero.QAutoRouter.Plugins.CPluginInterface" FILE "simplerouter.json")
    Q_INTERFACES(CPluginInterface)

	public:
		friend class CSegmentState;

        virtual tPluginType			type();							/** is the a router or post-router */

        virtual QString				title() const;					/** a brief name for the plugin */
        virtual QString				version() const;				/** return a version number string */
        virtual QStringList			credits() const;				/** name of authors + email */
        virtual QString				website() const;				/** the author's website */
        virtual QString				description() const;			/** a brief description of the plugin */
        virtual QStringList			license() const;				/** the license text for the plugin */

		virtual bool				start(CPcb* pcb);				/** initialize, gets' called once prior to exec() being called */
		virtual void				stop();							/** stop processing */
		virtual bool				exec();							/** get's called repeatedly while exec() returns true, return false to stop */
		virtual QString				elapsed();						/** elapsed time of the run in hh:mm:ss format */

	signals:
		void						status(QString txt);			/** emit a status text */

	private:

		typedef enum {
			Idle,													/** there is nothing happening */
			Selecting,												/** selecting which net(s) to route */
			Routing,												/** committing a route */
		} tRunState;

		CPcb*						pcb() {return mPcb;}
		tRunState					state();
		bool						running() {return state() != Idle;}
		void						setState(tRunState state);
		QString						currentStatus();				/** a brief status report for the status bar */
        CPcbNet*                    selectNet();
        bool                        endPoints();
        QGraphicsPathItem*          drawRatLine();
        QGraphicsPathItem*          drawRatLine(QList<SimpleRouterNode> path);
        void                        route();
        QList<SimpleRouterNode>&    path();
        QList<SimpleRouterNode*>    neighbours(SimpleRouterNode* node);
        void                        open(SimpleRouterNode* node);
		void                        close(SimpleRouterNode* node);
		void                        clear(QList<SimpleRouterNode*>& nodes);
		double                      manhattanLength(QPointF a, QPointF b);
        double                      adjacentCost(QPointF a, QPointF b);
        double                      cost(SimpleRouterNode node);
        double                      g(SimpleRouterNode node);
        double                      h(SimpleRouterNode node);

        QList<SimpleRouterNode>     neighbours(SimpleRouterNode node);
    private:
        void                        insort(QList<SimpleRouterNode*>& list, SimpleRouterNode* node);

		CPcb*						mPcb;
		QDateTime					mStartTime;
		tRunState					mState;
		CPcbNet*                    mNet;                           /** the current net */
		CGPadstack*                 mEndPoint[2];                   /** current route end points */
		QGraphicsPathItem*          mRatLine;                       /** The current rat line */
		QList<SimpleRouterNode*>    mOpenList;
        QList<SimpleRouterNode*>    mClosedList;                    /** closed nodes ordered by cost */
        QList<SimpleRouterNode>     mPath;                          /** The resulting path */
};

#endif // SIMPLEROUTER_H
