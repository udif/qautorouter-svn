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
#ifndef CPCBNETWORK_H
#define CPCBNETWORK_H

#include <QObject>
#include <QString>

#include "cspecctraobject.h"

class CPcbNet;
class CPcbClass;
class CPcbNetwork : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcbNetwork(QGraphicsItem *parent = 0);
		virtual ~CPcbNetwork();

		int								nets();
		CPcbNet*						net(int idx);
		CPcbNet*						net(QString ref);
		QList<CPcbNet*>&				netsRef();


		int								netClasses();
		CPcbClass*						netClass(int idx);
		CPcbClass*						netClass(QString ref);

		int								routed();

	private:
		QList<CPcbNet*>					mNets;
		QList<CPcbClass*>				mClasses;

};

#endif // CPCBNETWORK_H

