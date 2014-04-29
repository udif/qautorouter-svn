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
#ifndef CPCLAYER_H
#define CPCLAYER_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QColor>

#include "cspecctraobject.h"

class CPcbType;
class CPcbLayer : public CSpecctraObject
{
	Q_OBJECT
	public:

		typedef enum
		{
			Horizontal,
			Vertical
		} tDirection;

		CPcbLayer(QGraphicsItem *parent = 0);
		virtual ~CPcbLayer();

		virtual QString					name();
		virtual QString					description();

		QColor							color() {return mColor;}
		CPcbType*						type();
		int								index();
		void							setDirection(tDirection direction) {mDirection = direction;}
		tDirection						direction() {return mDirection;}

		void							setColor(QColor color) {mColor=color;}

		void							fromBytes(QByteArray data);
		QByteArray						toBytes();
	private:
		QColor							mColor;
		tDirection						mDirection;
};

#endif // CPCBLAY_H

