/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARNODE_H
#define _CASTARNODE_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QList>

class CAStarNode
{
	/// @brief An node to explore a path using the A* algorithm

	public:

		CAStarNode(CAStarNode* parent=NULL);
		CAStarNode(QPoint pt, CAStarNode* parent=NULL);
		CAStarNode(QPoint pt, int cost, CAStarNode* parent=NULL);
		CAStarNode(const CAStarNode& other);
		~CAStarNode();

		CAStarNode& operator=(const CAStarNode& other);
		bool operator==(const CAStarNode& other) const;
		bool operator!=(const CAStarNode& other) const;
		bool operator<(const CAStarNode& other) const;
		bool operator>(const CAStarNode& other) const;

		int					x()								{return mPos.x();}
		int					y()								{return mPos.y();}
		void				setX(int x)						{mPos.setX(x);}
		void				setY(int y)						{mPos.setY(y);}
		void				setPos(int x, int y)			{mPos.setX(x),mPos.setY(y);}
		void				setPos(QPoint pos)				{mPos=pos;}
		QPoint				pos()							{return mPos;}

		void				open()							{mOpen=true;}
		void				close()							{mOpen=false;}

		bool				isOpen()						{return mOpen;}
		bool				isClosed()						{return !mOpen;}

		void				clear();

		CAStarNode*			parent()						{return mParent;}
		QList<CAStarNode*>&	children()						{return mChildren;}

		int					cost()							{return g() + h();}

		bool				seek();

	protected:

		static void			setBounds(QRect r)				{mBounds=r;}
		static QRect&		bounds()						{return mBounds;}

		static void			setStart(QPoint pt)				{mStart=pt;}
		static QPoint&		start()							{return mStart;}

		static void			setGoal(QPoint pt)				{mGoal=pt;}
		static QPoint&		goal()							{return mGoal;}

	private:

		void				instantiateNeighbors();
		void				insort(CAStarNode* child);
		bool				isTraversable(QPoint& pt);
		int					manhattanLength(QPoint& a, QPoint& b);
		int					adjacentCost(QPoint& a, QPoint& b);

		int					g();
		int					h();

		static QRect		mBounds;
		static QPoint		mStart;
		static QPoint		mGoal;

		CAStarNode*			mParent;
		QPoint				mPos;
		int					mCost;
		bool				mOpen;
		QList<CAStarNode*>	mChildren;
		int					mG;
		int					mH;
};


#endif // _CASTARNODE_H
