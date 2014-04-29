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
#include "cgpadstack.h"
#include "cpcbplace.h"
#include "cpcb.h"
#include "cpcbstructure.h"
#include "cpcblayer.h"

QMap<QString,CGPadstack*>	CGPadstack::mGPadstacks; /** indexed by "UNIT-PIN" string notation. */

#define inherited CGSegment

CGPadstack::CGPadstack(CPcbNet* net,CPcbPlace* place,QString pinRef, QObject* /* parent */)
: inherited(net)
, mPlace(place)
, mPinRef(pinRef)
{
	mGPadstacks.insert(unitRef(),this);
}

CGPadstack::~CGPadstack()
{
	QList<QString> keys = mPads.keys();
	for(int n=0; n < keys.count(); n++)
	{
		delete mPads[keys[n]];
	}
	mGPadstacks.take(unitRef());
}

/**
  * @brief convinience function to get the root pcb pointer
  */
CPcb* CGPadstack::pcb()
{
	if ( place() != NULL )
	{
		return place()->pcb();
	}
	return NULL;
}

/**
  * @brief Add a pad to the padstack.
  */
void CGPadstack::addPad(CGPad* pad)
{
	mPads.insert(pad->layer(),pad);
}

/**
  * @return a pointer to a CGpadstack object by unit reference notation "UNIT-PIN".
  */
CGPadstack* CGPadstack::padstack(QString& unitRef)
{
	if ( padstacks().contains(unitRef) )
	{
		return padstacks()[unitRef];
	}
	return NULL;
}

/**
  * @return UNIT-PIN notation.
  */
QString& CGPadstack::unitRef()
{
	if ( mUnitRef.isEmpty() )
	{
		mUnitRef = place()->unit()+"-"+pinRef();
	}
	return mUnitRef;
}

/**
  * @return the pin reference for this padstack.
  */
QString& CGPadstack::pinRef()
{
	return mPinRef;
}

CPcbPlace* CGPadstack::place()
{
	return mPlace;
}

/**
  * @param layer name of layer
  * @return a layer by name
  */
CGPad* CGPadstack::pad(QString layer)
{
	if ( mPads.contains(layer) )
	{
		return mPads[layer];
	}
	return NULL;
}

/**
  * @return a point which is the center of the padstack
  */
QPointF CGPadstack::origin()
{
	QPointF pt;
	QStringList layers = this->layers();
	for(int n=0; n < layers.count(); n++)
	{
		CGPad* pPad = pad(layers.at(n));
		pt = pPad->pos();
	}
	return pt;
}

/**
  * @return the names of the layers that have pads
  */
QStringList CGPadstack::layers()
{
	QStringList rc;
	QMap<QString, CGPad*>::iterator i;
	for (i = mPads.begin(); i != mPads.end(); ++i)
		rc.append( i.key());
	return rc;
}

/**
  * @return the shape outline of the padstack.
  */
QPainterPath CGPadstack::shape() const
{
	QPainterPath ppath;
#if 1
	CGPadstack* me = (CGPadstack*)this;
	for(int n=0; n < me->layers().count(); n++)
	{
		CGPad* pPad = me->pad(me->layers().at(n));
		ppath.addPath(pPad->shape());
	}
#endif
	return ppath;
}

QRectF CGPadstack::boundingRect() const
{
	QRectF rc;
	QPainterPath ppath;
	CGPadstack* me = (CGPadstack*)this;
	for(int n=0; n < me->layers().count(); n++)
	{
		CGPad* pPad = me->pad(me->layers().at(n));
		ppath.addPath(pPad->shape());
	}
	rc = ppath.boundingRect();
	return rc;
}


