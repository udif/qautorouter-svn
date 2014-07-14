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
#include <QVector>
#include <QPoint>
#include <QPointF>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <cplugininterface.h>
#include <simpleroutergrid.h>

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
        } runState_t;

		CPcb*						pcb() {return mPcb;}
        runState_t					state();
		bool						running() {return state() != Idle;}
        void						setState(runState_t state);
		QString						currentStatus();				/** a brief status report for the status bar */
        CPcbNet*                    selectNet();
        bool                        endPoints();
        QGraphicsPathItem*          drawRatLine();
        void                        drawPath(QPoint a, QPoint b);
        void                        drawPath();
        void                        route();

        void                        resizeGrid();
        bool                        endPath(QPoint src, QPoint dst);
        void                        getPath(QPoint src, QPoint dst);
        int                         nextNode(QPoint destination, QPoint& next);

        inline bool                 traversed(int x, int y)
        {
            return (mGrid.get(x,y)==SimpleRouterGrid::nSeen);
        }

        inline bool                 blocked(int x, int y)
        {
            return (mGrid.get(x,y)==SimpleRouterGrid::nBlocked);
        }

        inline bool                 traversable(int x, int y)
        {
            return (!traversed(x,y) && !blocked(x,y));
        }

        inline int                  sDistance(QPoint src, QPoint dst)
        {
            //add 10 for N,E,S,W (straight)
            int distance = 10;

            //now add manhattan length
            distance += abs(src.x() * 10 - dst.x() * 10);
            distance += abs(src.y() * 10 - dst.y() * 10);
            return distance;
        }

        inline int                  dDistance(QPoint src, QPoint dst)
        {
            //add 10 for NE,SE,SW,NW (diagonal)
            int distance = 14;

            //now add manhattan length
            distance += abs(src.x() * 10 - dst.x() * 10);
            distance += abs(src.y() * 10 - dst.y() * 10);
            return distance;
        }

        int                         CheckN(QPoint& dst, QPoint& outNode);
        int                         CheckE(QPoint& dst, QPoint& outNode);
        int                         CheckS(QPoint& dst, QPoint& outNode);
        int                         CheckW(QPoint& dst, QPoint& outNode);
        int                         CheckNE(QPoint& dst, QPoint& outNode);
        int                         CheckSE(QPoint& dst, QPoint& outNode);
        int                         CheckSW(QPoint& dst, QPoint& outNode);
        int                         CheckNW(QPoint& dst, QPoint& outNode);

    private:
        SimpleRouterGrid            mGrid;
        QVector<QPoint>             mPath;
		CPcb*						mPcb;
		QDateTime					mStartTime;
        runState_t					mState;
		CPcbNet*                    mNet;                           /** the current net */
		CGPadstack*                 mEndPoint[2];                   /** current route end points */
		QGraphicsPathItem*          mRatLine;                       /** The current rat line */
};

#endif // SIMPLEROUTER_H
