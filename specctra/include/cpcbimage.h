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
#ifndef CPCBIMAGE_H
#define CPCBIMAGE_H

#include <QObject>
#include <QString>

#include "cspecctraobject.h"

class CPcbOutline;
class CPcbPin;
class CPcbImage : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbImage(QGraphicsItem *parent = 0);
		virtual ~CPcbImage();

		virtual QString					name();
		int								outlines();
		CPcbOutline*					outline(int idx);

		int								pins();
		CPcbPin*						pin(int idx);
		CPcbPin*						pin(QString ref);

        /* gEDA export methods */
        virtual QList<CSpecctraObject*>	gedaChildren();

private:
		QList<CPcbOutline*>				mOutlines;
		QList<CPcbPin*>					mPins;

};

#endif // CPCBIMAGE_H

