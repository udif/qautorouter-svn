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
#include "cpcbpins.h"
#include "cpcbplace.h"
#include "cpcbplacement.h"
#include "cpcb.h"
#include "cpcbshape.h"

#include <QStringList>
#define inherited CSpecctraObject

CPcbPins::CPcbPins(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbPins::~CPcbPins()
{
}

int CPcbPins::pinRefs()
{
	return properties().count();
}

QString CPcbPins::pinRef(int idx)
{
	QString rc;
	if ( idx < properties().count() )
	{
		rc = properties().at(idx);
	}
	return rc;
}

