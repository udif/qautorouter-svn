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
#ifndef CPCSTRUCTUREB_H
#define CPCSTRUCTUREB_H

#include <QObject>
#include <QList>
#include "cspecctraobject.h"

class CPcbBoundary;
class CPcbLayer;
class CPcbRule;
class CPcbStructure : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbStructure(QGraphicsItem *parent = 0);
		virtual ~CPcbStructure();

		int								layers();
		CPcbLayer*						layer(int idx);
		CPcbLayer*						layer(QString ref);
		int								indexOf(CPcbLayer* layer);

		CPcbBoundary*					boundary();

        virtual QList<CSpecctraObject*>	gedaChildren();

};

#endif // CPCSTRUCTUREB_H

