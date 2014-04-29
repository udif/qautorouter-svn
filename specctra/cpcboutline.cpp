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
#include "cpcboutline.h"
#include "cpcbimage.h"
#include "cpcbpath.h"

#define inherited CSpecctraObject

CPcbOutline::CPcbOutline(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbOutline::~CPcbOutline()
{
}
/**
  * @return the component count
  */
int CPcbOutline::paths()
{
	return childCount("path");
}

/**
  * @return a component by index
  */
CPcbPath* CPcbOutline::path(int idx)
{
	return (CPcbPath*)child("path",idx);
}

/**
  * @brief path
  */
CPcbPath* CPcbOutline::path()
{
	return path(0);
}

