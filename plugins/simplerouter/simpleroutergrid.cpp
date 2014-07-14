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
#include "simpleroutergrid.h"

SimpleRouterGrid::SimpleRouterGrid(int width,int height)
: mNode(NULL)
{
    resize(QSize(width,height));
}

SimpleRouterGrid::~SimpleRouterGrid()
{
    clear();
}

void SimpleRouterGrid::clear()
{
    if ( mNode )
    {
        delete mNode;
        mNode = NULL;
    }
    mSize = QSize(0,0);
}

void SimpleRouterGrid::fill(node_t t)
{
    for(int x=0; x < mSize.width(); x++)
    {
        for(int y=0; y < mSize.height(); y++)
        {
            set(x,y,t);
        }
    }
}

QSize SimpleRouterGrid::size()
{
    return mSize;
}

void SimpleRouterGrid::resize(QSize size)
{
    clear();
    mNode = new node_t [size.width()*size.height()];
    mSize = size;
    fill(nUndefined);
}

void SimpleRouterGrid::set(int x, int y, node_t t)
{
    mNode[indexOf(x,y)] = t;
}

void SimpleRouterGrid::set(QPoint pt, node_t t)
{
    set(pt.x(),pt.y(),t);
}

SimpleRouterGrid::node_t SimpleRouterGrid::get(int x, int y)
{
    node_t rc = mNode[indexOf(x,y)];
    return rc;
}

SimpleRouterGrid::node_t SimpleRouterGrid::get(QPoint pt)
{
    return get(pt.x(),pt.y());
}

/**
 * @brief Translate x,y coordinate to a linear offet.
 */
int SimpleRouterGrid::indexOf(int x, int y)
{
    int rc = (y*mSize.width()) + x;
    return rc;
}

QPoint SimpleRouterGrid::translate(QPoint pt)
{
    #if 1
        QPoint rc;
        rc.setX( pt.x() + mTranslation.x() );
        rc.setY( pt.y() + mTranslation.y() );
        rc.setX( ( width() - rc.x() ) -1 );
        rc.setY( ( height() - rc.y() ) -1 );
        return rc;
    #else
        QPoint rc;
        rc.setX( pt.x() + mTranslation.x() );
        rc.setY( pt.y() + mTranslation.y() );
        return rc;
    #endif
}


QPoint SimpleRouterGrid::translate(QPointF pt)
{
    return translate(QPoint((int)pt.x(),(int)pt.y()));
}

