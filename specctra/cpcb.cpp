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
#include "cpcb.h"
#include "cpcbstructure.h"
#include "cpcbplacement.h"
#include "cpcblibrary.h"
#include "cpcbnetwork.h"
#include "cpcbboundary.h"

#include <QEventLoop>

#define inherited CSpecctraObject

CPcb::CPcb(QGraphicsItem *parent)
: inherited(parent)
, mStructure(NULL)
, mPlacement(NULL)
, mLibrary(NULL)
, mNetwork(NULL)

{
}

CPcb::~CPcb()
{
}

/**
  * @brief provide a hook for plugin to yield...
  */
void CPcb::yield()
{
	QEventLoop loop;
	loop.processEvents();
}

/**
  * @brief span the object tree and extract each object's gEDA translation.
  */
QString CPcb::toGeda(int lvl)
{
    QString fill;
    QString text;
    fill.fill(' ',lvl*2);
    if ( gedaObjectClass().length() )
    {
        text += fill;
        text += "["+gedaObjectClass()+" "+gedaProperties().join(" ")+"]\n";
    }
    for(int n=0;n<children().count();n++)
    {
        CSpecctraObject* child = children().at(n);
        text += child->toGeda(lvl);
    }
    return text;

}

/**
  * @brief gEDA export method.
  * @return Translated gEDA object class name.
  */
QString CPcb::gedaObjectClass()
{
    return "PCB";
}

/**
  * @brief gEDA export method.
  * @return Translated gEDA object properties.
  */
QStringList CPcb::gedaProperties()
{
    QStringList rc;
    if ( properties().count() )
    {
        CPcbStructure* structure = (CPcbStructure*)child("structure");
        if ( structure != NULL )
        {
            CPcbBoundary* boundary = structure->boundary();
            if ( boundary != NULL )
            {
                rc << "\"" + properties().at(0) + "\"";                     /* Name */
                rc << QString::number(boundary->boundingRect().width());    /* Width */
                rc << QString::number(boundary->boundingRect().height());   /* Height */
            }
        }
    }
    return rc;
}

/**
  * @brief gEDA export method.
  * @return Translated gEDA child object list.
  */
QList<CSpecctraObject*>	CPcb::gedaChildren()
{
    QList<CSpecctraObject*> rc;
    return rc;
}

/**
  * @return the pcb structure object
  */
CPcbStructure* CPcb::structure()
{
	if ( mStructure == NULL )
	{
		mStructure = (CPcbStructure*)child("structure");
	}
	return mStructure;
}

/**
  * @return the pcb placement object
  */
CPcbPlacement* CPcb::placement()
{
	if ( mPlacement == NULL )
	{
		mPlacement = (CPcbPlacement*)child("placement");
	}
	return mPlacement;
}

/**
  * @return the pcb library object
  */
CPcbLibrary* CPcb::library()
{
	if ( mLibrary == NULL )
	{
		mLibrary = (CPcbLibrary*)child("library");
	}
	return mLibrary;
}

/**
  * @return the pcb network object
  */
CPcbNetwork* CPcb::network()
{
	if ( mNetwork == NULL )
	{
		mNetwork = (CPcbNetwork*)child("network");
	}
	return mNetwork;
}

