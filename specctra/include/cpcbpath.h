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
#ifndef CPCBPATH_H
#define CPCBPATH_H

#include <QObject>
#include <QString>
#include <QPainterPath>
#include <QList>

#include "cspecctraobject.h"

class CPcbPath : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbPath(QGraphicsItem *parent = 0);
		virtual ~CPcbPath();

		QString							layer();
		double                          width();
		QPainterPath                    shape();
		QPainterPath                    oval();

		QList<QPointF>					polygon();

		/* gEDA export methods */
		virtual QString					gedaObjectClass();
		virtual QStringList				gedaProperties();
		virtual QList<CSpecctraObject*>	gedaChildren();

private:
		QPainterPath			circle(QPointF center,double radius);
		QPainterPath			mOval;
};

#endif // CPCBPATH_H

