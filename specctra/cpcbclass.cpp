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
#include "cpcbclass.h"
#include "cpcbnet.h"
#include "cpcbrule.h"
#include "cpcbwidth.h"

#define inherited CSpecctraObject

CPcbClass::CPcbClass(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbClass::~CPcbClass()
{
}


/**
  * @return the name of the net class.
  */
QString CPcbClass::name()
{
	QString nm;
	if ( properties().count() )
		nm = properties().at(0);
	return nm;
}

/**
  * @return a verbose description.
  */
QString CPcbClass::description()
{
	QString rc;
	rc += name()+" ";
	rc += QString::number(width())+"mil";
	return rc;
}

/**
  * @return the net count
  */
QStringList& CPcbClass::nets()
{
	if ( mNets.count() == 0 )
	{
		for( int n=1; n < properties().count(); n++)
		{
			mNets.append(properties().at(n));
		}
	}
	return mNets;
}

/**
  * @return the track width
  */
double CPcbClass::width()
{
	if ( rule() != NULL && rule()->width() != NULL )
		return rule()->width()->data();
	return 1;
}
