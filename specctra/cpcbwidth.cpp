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
#include "cpcbwidth.h"

#define inherited CSpecctraObject

CPcbWidth::CPcbWidth(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbWidth::~CPcbWidth()
{
}

/**
  * @brief set the track width
  */
void CPcbWidth::setData(double w)
{
	QString wStr = QString::number(w);
	if ( properties().isEmpty() )
		properties().append(wStr);
	properties()[0]=wStr;
}

/**
  * @return the default track width
  */
double CPcbWidth::data()
{
	double w=0;
	if ( !properties().isEmpty() )
		w = properties()[0].toDouble();
	return w;
}
