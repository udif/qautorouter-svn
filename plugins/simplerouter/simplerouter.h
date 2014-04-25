/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
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
#include <cplugininterface.h>

#include "castar.h"
#include "castarnode.h"

class CPcb;
class CPcbNet;
class CGSegment;
class SimpleRouter : public QObject, public CPluginInterface
 {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.pikeaero.QAutoRouter.Plugins.CPluginInterface" FILE "simplerouter.json")
    Q_INTERFACES(CPluginInterface)

	public:
		friend class CSegmentState;

		virtual tPluginType			type();							/* is the a router or post-router */

		virtual QString				title() const;					/* a brief name for the plugin */
		virtual QString				version() const;				/* return a version number string */
		virtual QStringList			credits() const;				/* name of authors + email */
		virtual QString				website() const;				/* the author's website */
		virtual QString				description() const;			/* a brief description of the plugin */
		virtual QStringList			license() const;				/* the license text for the plugin */

		virtual bool				start(CPcb* pcb);				/** initialize, gets' called once prior to exec() being called */
		virtual void				stop();							/** stop processing */
		virtual bool				exec();							/** get's called repeatedly while exec() returns true, return false to stop */
		virtual QString				elapsed();						/** elapsed time of the run in hh:mm:ss format */

	signals:
		void						status(QString txt);			/** emit a status text */
	protected:

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

		void						selectNet(CPcbNet* net,bool selected);
		void						select();
		void						route();
		void						route( QList<CAStarNode>& path, CGSegment* seg1, CGSegment* seg2);
		void						drawRatLine(CGSegment* seg1, CGSegment* seg2);
		QStack<CPcbNet*>&			netStack()	{return mNetStack;}
		QPointF						scenePt(QPoint gridPt);
		QPoint						gridPt(QPointF scenePt);
		void						gridPlotPt(QList<CAStarMarker>& grid, QPoint gridPt);
		void						gridPlotLine(QList<CAStarMarker>& grid, QPoint gridPt1,QPoint gridPt2);
		QList<CAStarMarker>&		keepOutList(CGSegment* exclude1, CGSegment* exclude2);
	private slots:
		void						slotOpen(QPoint pt);
		void						slotClose(QPoint pt);
	private:
		CPcb*						mPcb;
		QDateTime					mStartTime;
		tRunState					mState;
		QStack<CPcbNet*>			mNetStack;						/** the current work stack */
		QList<CAStarMarker>			mKeepOutList;
		double						mGridRez;
};

#endif // SIMPLEROUTER_H
