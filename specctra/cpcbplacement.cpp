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
#include "cpcbplacement.h"
#include "cpcbcomponent.h"
#include "cpcbplace.h"

#define inherited CSpecctraObject

CPcbPlacement::CPcbPlacement(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbPlacement::~CPcbPlacement()
{
}

/**
  * @return the component count
  */
int CPcbPlacement::components()
{
	if ( mComponents.count() == 0 )
	{
		for(int n=0;n<children().count();n++)
		{
			if ( children().at(n)->objectClass() == "component" )
			{
				mComponents.append((CPcbComponent*)children().at(n));
			}
		}
	}
	return mComponents.count();
}

/**
  * @return a component by index
  */
CPcbComponent* CPcbPlacement::component(int idx)
{
	if ( components() > idx)
	{
		return mComponents.at(idx);
	}
	return NULL;
}

/**
  * @return a component by footprint name
  */
CPcbComponent* CPcbPlacement::component(QString footprint)
{
	for(int n=0;n<components();n++)
	{
		if ( component(n)->footprint() == footprint)
		{
			return component(n);
		}
	}
	return NULL;
}

/**
  * @return search through aech components and return total places
  */
int CPcbPlacement::places()
{
	if ( mPlaces.count() == 0 )
	{
		for(int n=0;n<components();n++)
		{
			CPcbComponent* cobj = component(n);
			for( int j=0; j < cobj->places(); j++)
			{
				CPcbPlace* place = cobj->place(j);
				mPlaces.append(place);
			}
		}
	}
	return mPlaces.count();
}

/**
  * @return a place by index.
  */
CPcbPlace* CPcbPlacement::place(int idx)
{
	if ( places() >= idx)
	{
		return mPlaces.at(idx);
	}
	return NULL;
}

/**
  * @return a place by unit name.
  */
CPcbPlace* CPcbPlacement::place(QString uid)
{
	for(int n=0;n<places();n++)
	{
		if (mPlaces.at(n)->unit()==uid)
		{
			return mPlaces.at(n);
		}
	}
	return NULL;
}




