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
#ifndef CGVIA_H
#define CGVIA_H

#include <QObject>
#include <QPainterPath>
#include <QString>
#include <QGraphicsItem>
#include <QMap>
#include <cgpadstack.h>

class CPcbNet;
class CGVia : public CGPadstack
{
	Q_OBJECT
	public:
		CGVia(CPcbNet* net);
		virtual ~CGVia();

        virtual Segment_t           segmentType() {return Via;}
        virtual bool				isA(CGSegment::Segment_t t) {return t==Via || CGPadstack::isA(t);}

		virtual void				route();

	private:

};

#endif // CGVIA_H
