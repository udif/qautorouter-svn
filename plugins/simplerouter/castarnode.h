/*******************************************************************************
* Copyright (C) Pike Aerospace Research Corporation                            *
* Author: Mike Sharkey <mike@pikeaero.com>                                     *
*******************************************************************************/
#ifndef _CASTARNODE_H
#define _CASTARNODE_H

#include "castarmarker.h"

class CAStarNode : public CAStarMarker
{
	/// @brief An node to explore a path using the A* algorithm

	public:

		CAStarNode(CAStarNode* parent=NULL);
        CAStarNode(QPoint pt, CAStarNode* parent=NULL);
        CAStarNode(QPoint pt, double cost, CAStarNode* parent=NULL);
		CAStarNode(const CAStarNode& other);
		~CAStarNode();

        CAStarNode&             operator=(const CAStarNode& other);
        bool                    operator==(const CAStarNode& other) const;
        bool                    operator!=(const CAStarNode& other) const;
        bool                    operator<(const CAStarNode& other);
        bool                    operator>(const CAStarNode& other);

        void                    setParent(CAStarNode* parent)   {mParent=parent;}
		CAStarNode*				parent()						{return mParent;}

        void                    setCost(double cost)            {mCost=cost;}
        double                  cost()                          {return mCost;}

	private:

		CAStarNode*				mParent;
		double					mCost;


};


#endif // _CASTARNODE_H
