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
#ifndef CPCBPIN_H
#define CPCBPIN_H

#include <QObject>
#include <QString>
#include <QPointF>

#include "cspecctraobject.h"

class CPcbClearanceClass;
class CPcbPadstack;
class CPcbPin : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbPin(QGraphicsItem *parent = 0);
		virtual ~CPcbPin();

		virtual QString			name();
		QPointF					pos();
		QString					padstackName();
		CPcbPadstack*			padstack();
		CPcbClearanceClass*		clearanceClass();

        /* gEDA export methods */
        virtual QString					gedaObjectClass();
        virtual QStringList				gedaProperties();
        virtual QList<CSpecctraObject*>	gedaChildren();
};

#endif // CPCBPIN_H

