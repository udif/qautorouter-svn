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
#ifndef SIMPLEROUTER_GRID_H
#define SIMPLEROUTER_GRID_H

#include <QObject>
#include <QRectF>
#include <QPoint>
#include <QPointF>
#include <QSize>

class SimpleRouterGrid : public QObject
{
    Q_OBJECT

    public:

        typedef enum
        {
            nUndefined=0,
            nBlocked,               /* Blocked list */
            nOpen,                  /* Open list */
            nSource,
            nDestination,
            nSeen                   /* Already seen it */
        } node_t;

        SimpleRouterGrid(int width=0,int height=0);
        virtual ~SimpleRouterGrid();

        void                        clear();

        void                        resize(QSize size);
        QSize                       size();

        inline int                  width() {return mSize.width();}
        inline int                  height() {return mSize.height();}

        void                        fill(node_t t);

        void                        set(int x, int y, node_t t);
        void                        set(QPoint pt, node_t t);

        node_t                      get(int x, int y);
        node_t                      get(QPoint pt);

        inline void                 setTranslation(QPoint pt) {mTranslation=pt;}
        inline QPoint&              translation() {return mTranslation;}

        QPoint                      translate(QPoint pt);
        QPoint                      translate(QPointF pt);

	private:
        int                         indexOf(int x, int y);
        node_t*                     mNode;                          /** node data */
        QSize                       mSize;                          /** size of grid */
        QPoint                      mTranslation;                   /** translation offset */
};

#endif // SIMPLEROUTER_GRID_H
