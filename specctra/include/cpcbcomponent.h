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
#ifndef CPCBCOMPONENT_H
#define CPCBCOMPONENT_H

#include <QObject>
#include <QString>

#include "cspecctraobject.h"

class CPcbPlace;
class CPcbComponent : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbComponent(QGraphicsItem *parent = 0);
		virtual ~CPcbComponent();

		QString							footprint();
		int								places();
		CPcbPlace*						place(int idx);
};

#endif // CPCBCOMPONENT_H

