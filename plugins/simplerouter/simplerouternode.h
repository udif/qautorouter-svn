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
#ifndef SIMPLEROUTERNODE_H
#define SIMPLEROUTERNODE_H

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

class SimpleRouterNode
{
    public:
        SimpleRouterNode(SimpleRouterNode* parent=NULL)
        : mParent(parent)
        , mPos(0,0)
        , mScore(0.0)
        , mLayer(0)
        {}

        SimpleRouterNode(QPointF pos,int layer=0)
        : mParent(NULL)
        , mPos(pos)
        , mScore(0.0)
        , mLayer(layer)
        {}

        SimpleRouterNode(const SimpleRouterNode& other)
        : mParent(other.mParent)
        , mPos(other.mPos)
        , mScore(other.mScore)
        , mLayer(other.mLayer)
        {}

        /* node assignment/equality */
        SimpleRouterNode&       operator=(const SimpleRouterNode& other);
        bool                    operator==(const SimpleRouterNode& other) const;
        bool                    operator!=(const SimpleRouterNode& other) const;

        /* point assignment/equality */
        SimpleRouterNode&       operator=(const QPointF& other);
        bool                    operator==(const QPointF& other) const;
        bool                    operator!=(const QPointF& other) const;

        /* score assignment/comparators */
        SimpleRouterNode&       operator=(const double& other);
        bool                    operator==(const double& other) const;
        bool                    operator!=(const double& other) const;
        bool                    operator>=(const double& other) const;
        bool                    operator<=(const double& other) const;
        bool                    operator>(const double& other) const;
        bool                    operator<(const double& other) const;
        bool                    operator>=(const SimpleRouterNode& other) const;
        bool                    operator<=(const SimpleRouterNode& other) const;
        bool                    operator>(const SimpleRouterNode& other) const;
        bool                    operator<(const SimpleRouterNode& other) const;

        /* property setters/getters */
        void                    setParent(SimpleRouterNode* parent) {mParent=parent;}
        SimpleRouterNode*       parent()                            {return mParent;}
        int                     x()                                 {return mPos.x();}
        int                     y()                                 {return mPos.y();}
        void					setX(double x)                      {mPos.setX(x);}
        void					setY(double y)                      {mPos.setY(y);}
        void					setPos(int x, int y)                {mPos.setX(x),mPos.setY(y);}
        void					setPos(QPointF pos)                 {mPos=pos;}
        QPointF					pos()                               {return mPos;}
        void                    setScore(double score)              {mScore = score;}
        double                  score()                             {return mScore;}

    private:
        SimpleRouterNode*       mParent;        // parent node
        QPointF                 mPos;           // position point
        double                  mScore;         // tentative estimate
        int                     mLayer;         // layer index
};


#endif // SIMPLEROUTERNODE_H
