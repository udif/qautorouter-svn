/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARNODE_H
#define _CASTARNODE_H

#include <QObject>
#include <QList>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPointF>
#include <QRectF>

class CAStarNode
{
	/// @brief An node to explore a path using the A* algorithm

	public:

		CAStarNode(CAStarNode* parent=NULL);
		CAStarNode(QPointF pt, CAStarNode* parent=NULL);
		CAStarNode(QPointF pt, double cost, CAStarNode* parent=NULL);
		CAStarNode(const CAStarNode& other);
		~CAStarNode();

		CAStarNode& operator=(const CAStarNode& other);
		bool operator==(const CAStarNode& other) const;
		bool operator!=(const CAStarNode& other) const;
		bool operator<(const CAStarNode& other);
		bool operator>(const CAStarNode& other);

		double					x()								{return mPos.x();}
		double					y()								{return mPos.y();}
		void					setX(double x)					{mPos.setX(x);}
		void					setY(double y)					{mPos.setY(y);}
		void					setPos(double x, double y)		{mPos.setX(x),mPos.setY(y);}
		void					setPos(QPointF pos)				{mPos=pos;}
		QPointF					pos()							{return mPos;}

		void					open()							{mOpen=true;}
		void					close()							{mOpen=false;}

		bool					isOpen()						{return mOpen;}
		bool					isClosed()						{return !mOpen;}

		void					clear();

		CAStarNode*				root();
		CAStarNode*				parent()						{return mParent;}
		QList<CAStarNode*>&		children()						{return mChildren;}

		double					cost();

		QList<CAStarNode*>		path();

		static void				setBounds(QRectF r)				{mBounds=r;}
		static QRectF&			bounds()						{return mBounds;}

		static void				setStart(QPointF pt)			{mStart=pt;}
		static QPointF&			start()							{return mStart;}

		static void				setGoal(QPointF pt);
		static QPointF&			goal()							{return mGoalPt;}

        static void             setGoalRect(QRectF rect)        {mGoalRect=rect;}
        static QRectF&			goalRect()						{return mGoalRect;}

        static void				setScene(QGraphicsScene* scene)	{mScene=scene;}
		static QGraphicsScene*	scene()							{return mScene;}

		static void				setGridRez(double rez)			{mGridRez = rez;}
		static double			gridRez()						{return mGridRez;}

	private:

        bool					plot(QPointF& pt, QColor c);
        void					unplot();
        bool					seek();
		bool                    contains(QPointF& pt, CAStarNode* ignore=NULL);
		static QRectF			gridRect(QPointF pt);
		CAStarNode*				instantiateNeighbor(int x, int y);
		void					instantiateNeighbors();
		void					insort(CAStarNode* child);
		bool					isTraversable(QPointF& pt);
		double					manhattanLength(QPointF& a, QPointF& b);
		double					adjacentCost(QPointF& a, QPointF& b);

		double					g();
		double					h();

		static QRectF			mBounds;
		static QPointF			mStart;
		static QPointF			mGoalPt;
		static QRectF			mGoalRect;
		static QGraphicsScene*	mScene;
		static double			mGridRez;
        static QGraphicsItem*   mMarker;

		CAStarNode*				mParent;
		QPointF					mPos;
		double					mCost;
		bool					mOpen;
		QList<CAStarNode*>		mChildren;
		double					mG;
		double					mH;
        QList<QGraphicsItem*>	mPlot;

};


#endif // _CASTARNODE_H
