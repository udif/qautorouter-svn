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
#include "cpcblibrary.h"
#include "cpcbimage.h"
#include "cpcbpadstack.h"

#define inherited CSpecctraObject

CPcbLibrary::CPcbLibrary(QGraphicsItem *parent)
: inherited(parent)
{
}

CPcbLibrary::~CPcbLibrary()
{
}

/**
  * @return the image count
  */
int CPcbLibrary::images()
{
	return childCount("image");
}

/**
  * @return a image by index
  */
CPcbImage* CPcbLibrary::image(int idx)
{
	return (CPcbImage*)child("image",idx);
}

/**
  * @return a image by name
  */
CPcbImage* CPcbLibrary::image(QString name)
{
	int cc = childCount("image");
	for(int n=0; n<cc; n++)
	{
		CPcbImage* image = (CPcbImage*)child("image",n);
		if ( image->name() == name )
			return image;
	}
	return NULL;
}

/**
  * @return the padstack count
  */
int CPcbLibrary::padstacks()
{
	return childCount("padstack" );
}

/**
  * @return a padstack by index
  */
CPcbPadstack* CPcbLibrary::padstack(int idx)
{
	return (CPcbPadstack*)child("padstack",idx);
	return NULL;
}

/**
  * @return a padstack by name
  */
CPcbPadstack* CPcbLibrary::padstack(QString name)
{
	int cc = childCount("padstack");
	for(int n=0; n<cc; n++)
	{
		CPcbPadstack* padstack = (CPcbPadstack*)child("padstack",n);
		if ( padstack->name() == name )
			return padstack;
	}
	return NULL;
}
