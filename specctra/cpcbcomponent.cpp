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
#include "cpcbcomponent.h"

#define inherited CSpecctraObject

CPcbComponent::CPcbComponent(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbComponent::~CPcbComponent()
{
}

/**
  * @return footprint
  */
QString CPcbComponent::footprint()
{
	QString fp;
	if ( properties().count() )
	{
		fp = properties().at(0);
	}
	return fp;
}

/**
  * @return the component count
  */
int CPcbComponent::places()
{
	return childCount("place");
}

/**
  * @return a component by index
  */
CPcbPlace* CPcbComponent::place(int idx)
{
	return (CPcbPlace*)child("place",idx);
}
