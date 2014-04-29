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
#include "cgwire.h"
#include "cgvia.h"

#include <QMessageBox>

#define inherited CGSegment

CGWire::CGWire(CPcbNet* net)
: inherited(net)
{
}

CGWire::~CGWire()
{
}

CPcbNet* CGWire::net()
{
	if ( mNet != NULL )
	{
		return mNet;
	}
	return inherited::net();
}

/**
  * @return the shape of the wire segment
  */
QPainterPath CGWire::shape() const
{
	QPainterPath ppath;
	ppath.addPath(inherited::shape());
	return ppath;
}

/**
  * @brief break the wire into another segment at point
  */
bool CGWire::insertBreak(QPointF /* pt */,CGSegment::Segment_t style)
{
	bool rc=false;
	CGSegment* seg=NULL;
	switch(style)
	{
	default:
		QMessageBox::warning(NULL,tr("Invalid Segment"),tr("Program Error: CGWire::insertBreak(")+QString::number((int)style)+tr("): An invalid segment style was requested."));
		break;
	case CGSegment::Wire:
		seg = new CGWire(this->net());
		rc=true;
		break;
	case CGSegment::Via:
		seg = new CGVia(this->net());
		rc=true;
		break;
	}
	if ( seg != NULL )
	{
		for(int n=0; n < segmentsRef().count(); n++)
		{
			CGSegment* child = segmentsRef().at(n);
			seg->append(child);
		}
		segmentsRef().clear();
		append(seg);
	}
	return rc;
}

/**
 * @brief route the wire
 */
void CGWire::route()
{
}
