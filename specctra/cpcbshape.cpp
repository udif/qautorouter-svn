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
#include "cpcbshape.h"
#include "cpcbcircle.h"
#include "cpcbrect.h"
#include "cpcbpath.h"

#define inherited CSpecctraObject

CPcbShape::CPcbShape(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbShape::~CPcbShape()
{
}

QString CPcbShape::layer()
{
	QString sLayer;
	CSpecctraObject* child = children().at(0);
	if ( child->objectClass() == "circle" )
	{
		CPcbCircle* circle = (CPcbCircle*)child;
		sLayer = circle->layer();
	}
	else if ( child->objectClass() == "rect")
	{
		CPcbRect* rect = (CPcbRect*)child;
		sLayer = rect->layer();
	}
	else if ( child->objectClass() == "path")
	{
		CPcbPath* path = (CPcbPath*)child;
		sLayer = path->layer();
	}
	return sLayer;
}

QPainterPath CPcbShape::shape()
{
	QPainterPath ppath;
	CSpecctraObject* child = children().at(0);
	if ( child->objectClass() == "circle")
	{
		CPcbCircle* circle = (CPcbCircle*)child;
		ppath = circle->path();
	}
	else if ( child->objectClass() == "rect")
	{
		CPcbRect* rect = (CPcbRect*)child;
		ppath = rect->path();
	}
	else if ( child->objectClass() == "path")
	{
		CPcbPath* path = (CPcbPath*)child;
        ppath = path->oval();
	}
	return ppath;
}

