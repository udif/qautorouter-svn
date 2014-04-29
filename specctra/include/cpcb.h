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
#ifndef CPCB_H
#define CPCB_H

#include <QObject>
#include "cspecctraobject.h"

class CPcbStructure;
class CPcbPlacement;
class CPcbLibrary;
class CPcbNetwork;
class CPcb : public CSpecctraObject
{
	Q_OBJECT
	public:
		CPcb(QGraphicsItem *parent = 0);
		virtual ~CPcb();

        CPcbStructure*                  structure();
        CPcbPlacement*                  placement();
        CPcbLibrary*                    library();
        CPcbNetwork*                    network();

        /* gEDA export methods */
        virtual QString					toGeda(int lvl=0);
        virtual QString					gedaObjectClass();
        virtual QStringList				gedaProperties();
        virtual QList<CSpecctraObject*>	gedaChildren();

public slots:
        void                            yield();
	signals:
        void                            status(QString txt);
	private:
        CPcbStructure*                  mStructure;
        CPcbPlacement*                  mPlacement;
        CPcbLibrary*                    mLibrary;
        CPcbNetwork*                    mNetwork;
};

#endif // CPCB_H

