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
#ifndef CPCPLACEMENT_H
#define CPCPLACEMENT_H

#include <QObject>
#include <QString>
#include <QPolygonF>
#include <QList>

#include "cspecctraobject.h"

class CPcbComponent;
class CPcbPlace;
class CPcbPlacement : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbPlacement(QGraphicsItem *parent = 0);
		virtual ~CPcbPlacement();

		int								components();
		CPcbComponent*					component(int idx);
		CPcbComponent*					component(QString footprint);

		int								places();
		CPcbPlace*						place(int idx);
		CPcbPlace*						place(QString uid);

	private:
		QList<CPcbComponent*>			mComponents;
		QList<CPcbPlace*>				mPlaces;
};

#endif // CPCPLACEMENT_H

