/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARNODE_H
#define _CASTARNODE_H

#include "castarmarker.h"

#include <QPoint>

class CAStarNode : public CAStarMarker
{
	/// @brief An node to explore a path using the A* algorithm

	public:

        CAStarNode();
        CAStarNode(QPoint pt, QPoint parent = QPoint(EMPTY_X,EMPTY_Y) );
		CAStarNode(const CAStarNode& other);
		~CAStarNode();

        CAStarNode&             operator=(const CAStarNode& other);
        bool                    operator<(const CAStarNode& other);
        bool                    operator>(const CAStarNode& other);
        bool                    operator<=(const CAStarNode& other);
        bool                    operator>=(const CAStarNode& other);

        void                    setParent(QPoint pt)            {mParent=pt;}
        QPoint                  parent()						{return mParent;}

        void                    setCost(double cost)            {mCost=cost;}
        double                  cost()                          {return mCost;}

	private:

        QPoint  				mParent;
		double					mCost;


};


#endif // _CASTARNODE_H
