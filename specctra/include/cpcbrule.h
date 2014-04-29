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
#ifndef CPCBRULE_H
#define CPCBRULE_H

#include <QObject>
#include <QString>
#include <QRectF>
#include <QPainterPath>

#include "cspecctraobject.h"

class CPcbWidth;
class CPcbClearance;
class CPcbRule : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbRule(QGraphicsItem *parent = 0);
		virtual ~CPcbRule();

		CPcbWidth*					width();

        int                         clearances();
        CPcbClearance*              clearance(int idx=0);
        double                      clearanceOf(QString type);
};

#endif // CPCBRULE_H

