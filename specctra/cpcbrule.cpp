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
#include "cpcbrule.h"
#include "cpcbwidth.h"
#include "cpcbclearance.h"

#define inherited CSpecctraObject

CPcbRule::CPcbRule(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbRule::~CPcbRule()
{
}


/**
  * @return the default track width
  */
CPcbWidth* CPcbRule::width()
{
	return (CPcbWidth*)child("width");
}

/**
  * @return the number of clearances
  */
int CPcbRule::clearances()
{
    int rc=0;
    for(int n=0; n < children().count(); n++)
    {
        if ( children().at(n)->objectClass() == "clearance" )
        {
            ++rc;
        }
    }
    return rc;
}

/**
  * @return The clearance specied by the index
  */
CPcbClearance* CPcbRule::clearance(int idx)
{
    for(int n=0; n < children().count() && idx>=0; n++)
    {
        if ( children().at(n)->objectClass() == "clearance" )
        {
            if ( (idx--) == 0 )
            {
                return (CPcbClearance*)children().at(n);
            }
        }
    }
    return NULL;
}

/**
  * @return the clearance for a specified type
  */
double CPcbRule::clearanceOf(QString type)
{
    /* look for the clearance for this class of object */
    for(int n=0; n < clearances(); n++ )
    {
        CPcbClearance* clearance = this->clearance(n);
        if ( clearance->type() == type )
        {
            return clearance->data();
        }
    }
    /* okay, look for the default... */
    for(int n=0; n < clearances(); n++ )
    {
        CPcbClearance* clearance = this->clearance(n);
        if ( clearance->type().isEmpty() )
        {
            return clearance->data();
        }
    }
    return 8.0; /* FIXME - can we get another default from somewhere in this case? */
}

