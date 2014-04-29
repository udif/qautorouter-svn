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
#ifndef CUTIL_H
#define CUTIL_H

#include <QString>
#include <QList>
#include <QPointF>

class CGPadstack;
class CPcbNet;
class CUtil
{
	public:
		typedef enum {
			Ascending,
			Descending,
		} tSortOrder;
		static QString				elapsed(int tm);
		static QString				unitRef(QString unitPinRef);
		static QString				pinRef(QString unitPinRef);
		static QString				placeRef(QString unitRef,QString pinRef);
		static int					sort(QList<CGPadstack*>& pads,QPointF pt,tSortOrder order=Ascending);
		static int					sort(QList<CPcbNet*>& nets,QPointF pt,tSortOrder order=Ascending);
};

#endif // CUTIL_H
