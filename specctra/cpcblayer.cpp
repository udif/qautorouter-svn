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
#include "cpcblayer.h"
#include "cpcbtype.h"
#include "cpcbstructure.h"

#include <QDataStream>
#include <QByteArray>

#define inherited CSpecctraObject

CPcbLayer::CPcbLayer(QGraphicsItem *parent)
: inherited(parent)
, mDirection(Horizontal)
{
	setColor(QColor(0xA0,0,0));
}

CPcbLayer::~CPcbLayer()
{
}

/**
  * @return the layer name
  */
QString CPcbLayer::name()
{
	return properties().at(0);
}

/**
  * @return the later type, signal, etc...
  */
CPcbType* CPcbLayer::type()
{
	return (CPcbType*)child("type");
}

/**
  * @brief @return the layer index...
  */
int CPcbLayer::index()
{
	CSpecctraObject* obj = parentObject();
	if ( obj != NULL && obj->objectClass() == "structure" )
	{
		CPcbStructure* structure = (CPcbStructure*)obj;
		return structure->indexOf(this);
	}
	return 0;
}

/**
  * @return detailed descriptionm string
  */
QString CPcbLayer::description()
{
	QString rc;
	rc += "["+QString::number(index())+"]";
	rc += name();
	rc += " ("+type()->data()+") ";
	if ( direction() == Horizontal )
		rc += "Horizontal";
	else
		rc += "Vertical";
	return rc;
}

void CPcbLayer::fromBytes(QByteArray data)
{
	int i=0;
	QDataStream in(&data,QIODevice::ReadOnly);
	in >> mColor;
	in >> i; mDirection=(CPcbLayer::tDirection)i;
}

QByteArray CPcbLayer::toBytes()
{
	QByteArray data;
	QDataStream out(&data,QIODevice::WriteOnly);
	out << color();
	out << (int)mDirection;
	return data;
}


