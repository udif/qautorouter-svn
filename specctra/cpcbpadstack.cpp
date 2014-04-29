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
#include "cpcbpadstack.h"

#define inherited CSpecctraObject

CPcbPadstack::CPcbPadstack(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbPadstack::~CPcbPadstack()
{
}

QString CPcbPadstack::name()
{
	return properties().at(0);
}

int CPcbPadstack::shapes()
{
	int count = 0;
	for( int n=0; n < children().count(); n++ )
	{
		if ( children().at(n)->objectClass() == "shape")
		{
			++count;
		}
	}
	return count;
}

CPcbShape* CPcbPadstack::shape(int idx)
{
	if ( idx < children().count() )
		return (CPcbShape*)children().at(idx);
	return NULL;
}

