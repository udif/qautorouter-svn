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
#ifndef CPCBSHAPE_H
#define CPCBSHAPE_H

#include "cspecctraobject.h"

#include <QObject>
#include <QString>
#include <QPolygonF>
#include <QStringList>
#include <QPainterPath>

class CPcbShape : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbShape(QGraphicsItem *parent = 0);
		virtual ~CPcbShape();

		QString				layer();
		QPainterPath		shape();
};

#endif // CPCBSHAPE_H

