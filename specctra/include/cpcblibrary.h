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
#ifndef CPCBLIBRARY_H
#define CPCBLIBRARY_H

#include <QObject>
#include <QString>

#include "cspecctraobject.h"

class CPcbImage;
class CPcbPadstack;
class CPcbLibrary : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbLibrary(QGraphicsItem *parent = 0);
		virtual ~CPcbLibrary();

		int								images();
		CPcbImage*						image(int idx);
		CPcbImage*						image(QString ref);

		int								padstacks();
		CPcbPadstack*					padstack(int idx);
		CPcbPadstack*					padstack(QString ref);
};

#endif // CPCBLIBRARY_H

