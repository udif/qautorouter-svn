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
#ifndef CGWIRE_H
#define CGWIRE_H

#include <QObject>
#include <QList>
#include <QPointF>
#include <QPainterPath>

#include "cgsegment.h"

class CPcbNet;
class CGWire : public CGSegment
{
	Q_OBJECT
	public:
		CGWire(CPcbNet *net);
		virtual ~CGWire();

        virtual Segment_t   		segmentType() {return Wire;}
        virtual bool				isA(CGSegment::Segment_t t) {return t==Wire || CGSegment::isA(t);}

        virtual CPcbNet*			net();

        virtual bool				insertBreak(QPointF pt,CGSegment::Segment_t style);

		virtual QPainterPath		shape() const;

		virtual void				route();
};

#endif // CGWIRE_H
